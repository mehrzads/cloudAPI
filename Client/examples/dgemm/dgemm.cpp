/*
 *
 * Author: Mehrzad Samadi
 * First Client Service
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h> 
#include <chrono>
#include "cloud.h"
#include "cloudTimer.h"
#include "clblas.h"





int main(int argc, char *argv[])
{
  int sockfd, portno;
  
  // Reading the arguments
  if (argc < 3) {
     fprintf(stderr,"usage %s hostname port\n", argv[0]);
     exit(0);
  }
  portno = atoi(argv[2]);
  char * hostname = argv[1];

  double * c_A;
  double * c_B;
  double * c_C;
  cloudInit(portno, hostname, sockfd);
  int N = 1024;
  int size = N * N;
  double * A = (double *) malloc( size * sizeof(double));
  double * B = (double *) malloc( size * sizeof(double));
  double * C = (double *) malloc( size * sizeof(double));
  double * C_ref = (double *) malloc( size * sizeof(double));
  cloudMalloc(sockfd, (void **)&c_A, size * sizeof(double));
  cloudMalloc(sockfd, (void **)&c_B, size * sizeof(double));
  cloudMalloc(sockfd, (void **)&c_C, size * sizeof(double));
    
  for (int i = 0; i < size; i++){
      A[i] = double(rand())/INT_MAX;
      B[i] = double(rand())/INT_MAX;
      C_ref[i] = 0;
      C[i] = 0;
  }

  CloudTimer cloudTimer;
  cloudTimer.start();
  
  cloudMemcpy(sockfd,  c_A,  A,  size * sizeof(double), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
  cloudMemcpy(sockfd,  c_B,  B,  size * sizeof(double), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
  
 // matrixMultiply(sockfd, N, N, N , c_A, c_B, c_C);
  cloudDgemm(sockfd, ClblasRowMajor, ClblasNoTrans, ClblasNoTrans, N, N, N, 1.0, c_A, N, c_B, N, 0.0, c_C, N);
  
  cloudMemcpy(sockfd,  C,  c_C,  size * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
  
  cloudTimer.end();    
  double time_in_seconds = cloudTimer.getDurationInSeconds();
  
  printf("Transfer from server %f ms\n", time_in_seconds * 1000);
  printf("Transfer rate %f Gbps\n", (size * sizeof(double) * 8 * 2 )/(1024 * 1024 *1024 *time_in_seconds) );
            
  
  for (int i = 0 ; i < N ; i++)
    for (int j = 0; j < N; j++) {
      double sum = 0;
      for (int k = 0; k < N; k++)
	sum = A[i * N + k] * B[k * N + j];
      C_ref[i * N + j] = sum;
  }

    
  int ferror = 0;
  for (int i = 0; i < size ; i++)
     if (C[i] != C_ref[i])
       ferror =1;
  if (ferror ==0)
     printf("Passed\n");
  else
     printf("Failed\n");       

  free(A);
  free(B);
  free(C);
  free(C_ref);
  cloudFree(sockfd, c_A);
  cloudFree(sockfd, c_B);
  cloudFree(sockfd, c_C);
  cloudFinish(sockfd);
  return 0;
}
