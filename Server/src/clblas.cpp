#include <utility>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include <math.h>              /* Basic Linear Algebra I/O */
#include "mpi.h"
#include "common.h" 
#include "clblas.h" 
#include "clblasargs.pb.h" 
#include "scalapack.h"
#include "server.h"

using namespace std;
using namespace clblasargs;
DGEMMMessage dgemmMessage;
CBLAS_ORDER OrderTransTable[]={CblasRowMajor, CblasColMajor};
CBLAS_TRANSPOSE TransposeTransTable[]={CblasNoTrans, CblasTrans, CblasConjTrans};


void lapack_dgemm(CLBLAS_ORDER Order, CLBLAS_TRANSPOSE TRANSA, CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC, MPIInfo mpiInfo){

    int numthreads = 8;
    openblas_set_num_threads( numthreads );
    // A     B       C
    // m x k k x n = m x n

    // nprows: process grid, number rows
    // npcols: process grid, number cols
    // myrow: process grid, our row
    // mycol: process grid, our col
    int nb=min(N/mpiInfo.nProcs,128);

    int mp = numroc( M, nb, mpiInfo.myRow, 0, mpiInfo.nRows ); // mp number rows A owned by this process
    int kp = numroc( K, nb, mpiInfo.myRow, 0, mpiInfo.nRows ); // kp number rows B owned by this process
    int kq = numroc( K, nb, mpiInfo.myCol, 0, mpiInfo.nCols ); // kq number cols A owned by this process
    int nq = numroc( N, nb, mpiInfo.myCol, 0, mpiInfo.nCols ); // nq number cols B owned by this process

    struct DESC desca, descb, descc;
    descinit( (&desca), M, K, nb, nb, 0, 0, mpiInfo.grid, max(1, mp) );
    descinit( (&descb), K, N, nb, nb, 0, 0, mpiInfo.grid, max(1, kp) );
    descinit( (&descc), M, N, nb, nb, 0, 0, mpiInfo.grid, max(1, mp) );
    double *ipa = new double[desca.LLD_ * kq];
    double *ipb = new double[descb.LLD_ * nq];
    double *ipc = new double[descc.LLD_ * nq];
    
    /// Scatter
    int sendr = 0, sendc = 0, recvr = 0, recvc = 0;
    for (int r = 0; r < N; r += nb, sendr=(sendr+1)%mpiInfo.nRows) {
      sendc = 0;
      // Number of rows to be sent
      // Is this the last row block?
      int nr = nb;
      if (N-r < nb)
	  nr = N-r;
   
      for (int c = 0; c < N; c += nb, sendc=(sendc+1)%mpiInfo.nCols) {
	  // Number of cols to be sent
	  // Is this the last col block?
	  int nc = nb;
	  if (N-c < nb)
	      nc = N-c;
   
	  if (mpiInfo.rank == 0) {
	      // Send a nr-by-nc submatrix to process (sendr, sendc)
	      Cdgesd2d(mpiInfo.grid, nr, nc, A+N*c+r, N, sendr, sendc);
	      Cdgesd2d(mpiInfo.grid, nr, nc, B+N*c+r, N, sendr, sendc);
	  }
   
	  if (mpiInfo.myRow == sendr && mpiInfo.myCol == sendc) {
	      // Receive the same data
	      // The leading dimension of the local matrix is nrows!
	      Cdgerv2d(mpiInfo.grid, nr, nc, ipa+mp*recvc+recvr, mp, 0, 0);
	      Cdgerv2d(mpiInfo.grid, nr, nc, ipb+mp*recvc+recvr, mp, 0, 0);
	      recvc = (recvc+nc)%kq;
	  }
   
      }
   
      if (mpiInfo.myRow == sendr)
	  recvr = (recvr+nr)%mp;
    } 


    MPI_Barrier( MPI_COMM_WORLD );

    pdgemm( false, false, M, N, K, 1,
                      ipa, 1, 1, &desca, ipb, 1, 1, &descb,
                      1, ipc, 1, 1, &descc );
    
    MPI_Barrier( MPI_COMM_WORLD );
    sendr = 0;
    for (int r = 0; r < N; r += nb, sendr=(sendr+1)%mpiInfo.nRows) {
        sendc = 0;
        // Number of rows to be sent
        // Is this the last row block?
        int nr = nb;
        if (N-r < nb)
            nr = N-r;
 
        for (int c = 0; c < N; c += nb, sendc=(sendc+1)%mpiInfo.nCols) {
            // Number of cols to be sent
            // Is this the last col block?
            int nc = nb;
            if (N-c < nb)
                nc = N-c;
 
            if (mpiInfo.myRow == sendr && mpiInfo.myCol == sendc) {
                // Send a nr-by-nc submatrix to process (sendr, sendc)
                Cdgesd2d(mpiInfo.grid, nr, nc, ipc+mp*recvc+recvr, mp, 0, 0);
                recvc = (recvc+nc)%nq;
            }
 
            if (mpiInfo.rank == 0) {
                // Receive the same data
                // The leading dimension of the local matrix is nrows!
                Cdgerv2d(mpiInfo.grid, nr, nc, C+N*c+r, N, sendr, sendc);
            }
 
        }
 
        if (mpiInfo.myRow == sendr)
            recvr = (recvr+nr)%mp;
    }
    MPI_Barrier( MPI_COMM_WORLD );

    free(ipa);
    free(ipb);
    free(ipc);

}


cloudError_t cloudDgemm(CLBLAS_ORDER Order, CLBLAS_TRANSPOSE TRANSA, CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC, MPIInfo mpiInfo){

 // cblas_dgemm(OrderTransTable[Order], TransposeTransTable[TRANSA], TransposeTransTable[TRANSB], M,    N,    K, ALPHA,   A,   LDA, B, LDB, BETA, C,  LDC);
  lapack_dgemm(Order, TRANSA, TRANSB, M,    N,    K, ALPHA,   A,   LDA, B, LDB, BETA, C,  LDC, mpiInfo);
  return CloudSuccess; 
}
cloudError_t handleClblasFunction(cloudFunctionKind functionType, std::string argsMessage, MPIInfo mpiInfo)
{
  switch (functionType){
    case ClBlasDGEMM:
       dgemmMessage.ParseFromString(argsMessage);
       cloudDgemm(static_cast<CLBLAS_ORDER>(dgemmMessage.order()),
            static_cast<CLBLAS_TRANSPOSE>(dgemmMessage.transa()),
            static_cast<CLBLAS_TRANSPOSE>(dgemmMessage.transb()),
            dgemmMessage.m(),
            dgemmMessage.n(),
            dgemmMessage.k(),
            dgemmMessage.alpha(),
            reinterpret_cast<double *>(dgemmMessage.a()), dgemmMessage.lda(),
            reinterpret_cast<double *>(dgemmMessage.b()), dgemmMessage.ldb(),
            dgemmMessage.beta(),
            reinterpret_cast<double *>(dgemmMessage.c()), dgemmMessage.ldc(), 
	    mpiInfo
	    );
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
