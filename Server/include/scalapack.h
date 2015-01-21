#ifndef SCALAPACK_H
#define SCALAPACK_H

extern "C" {
    struct DESC{
        int DTYPE_;
        int CTXT_;
        int M_;
        int N_;
        int MB_;
        int NB_;
        int RSRC_;
        int CSRC_;
        int LLD_;
    } ;

    void blacs_pinfo_( int *iam, int *nprocs );
    void blacs_get_( int *icontxt, int *what, int *val );
    void blacs_gridinit_( int *icontxt, char *order, int *nprow, int *npcol );
    void blacs_gridinfo_( int *context, int *nprow, int *npcol, int *myrow, int *mycol );
    void blacs_gridexit_( int *context );
    void blacs_exit_( int *code );

    int numroc_( int *n, int *nb, int *iproc, int *isrcproc, int *nprocs );
    void descinit_( struct DESC *desc, int *m, int *n, int *mb, int *nb, int *irsrc, int *icsrc, int *ictxt, int *lld, int *info );
    void pdlaprnt_( int *m, int *n, double *a, int *ia, int *ja, struct DESC *desca, int *irprnt,
        int *icprnt, const char *cmatnm, int *nout, double *work, int cmtnmlen );
    void pdgemm_( char *transa, char *transb, int *m, int *n, int *k, double *alpha,
         double *a, int *ia, int *ja, struct DESC *desca, double *b, int *ib, int *jb,
        struct DESC *descb, double *beta, double *c, int *ic, int *jc, struct DESC *descc );
    void Cdgesd2d(int icontxt, int m, int n, double * A, int lda, int rsrc, int csrc);
    void Cdgerv2d(int icontxt, int m, int n, double *A, int lda, int rsrc, int csrc);
}

void blacs_pinfo( int *p, int *P );

int blacs_get( int icontxt, int what );

int blacs_gridinit( int icontxt, bool isColumnMajor, int nprow, int npcol );

void blacs_gridinfo( int context, int nprow, int npcol, int *myrow, int *mycol );

void blacs_gridexit( int context );

void blacs_exit( int code );

int numroc( int n, int nb, int iproc, int isrcproc, int nprocs );

void descinit( struct DESC *desc, int m, int n, int mb, int nb, int irsrc, int icsrc, int ictxt, int lld );

void pdlaprnt( int m, int n, double *A, int ia, int ja, struct DESC *desc, int irprnt,
    int icprnt, const char *cmatnm, int nout, double *work );

void pdgemm( bool isTransA, bool isTransB, int m, int n, int k, double alpha,
     double *a, int ia, int ja, struct DESC *desca, double *b, int ib, int jb,
    struct DESC *descb, double beta, double *c, int ic, int jc, struct DESC *descc );
#endif /* ifndef SCALAPACK_H */
