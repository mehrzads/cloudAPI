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
#include <math.h> 
#include <chrono>
#include "cloud.h"
#include "cloudTimer.h"
#include "clblas.h"



#define EPSILON 0.0001

int main(int argc, char *argv[])
{
  int portno;
  
  TCPSocket socket;
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
  cloudInit(portno, hostname, socket);
  int N = 8192;
  int size = N * N;
  double * A = (double *) malloc( size * sizeof(double));
  double * B = (double *) malloc( size * sizeof(double));
  double * C = (double *) malloc( size * sizeof(double));
  double * C_ref = (double *) malloc( size * sizeof(double));
  cloudMalloc(socket, (void **)&c_A, size * sizeof(double));
  cloudMalloc(socket, (void **)&c_B, size * sizeof(double));
  cloudMalloc(socket, (void **)&c_C, size * sizeof(double));
    
  for (int i = 0; i < size; i++){
      A[i] = double(rand())/INT_MAX;
      B[i] = double(rand())/INT_MAX;
      C_ref[i] = 0;
      C[i] = 0;
  }

  CloudTimer cloudTimer;
  cloudTimer.start();
  
  cloudMemcpy(socket,  c_A,  A,  size * sizeof(double), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
  cloudMemcpy(socket,  c_B,  B,  size * sizeof(double), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
  
 // matrixMultiply(sockfd, N, N, N , c_A, c_B, c_C);
  cloudDgemm(socket, ClblasRowMajor, ClblasNoTrans, ClblasNoTrans, N, N, N, 1.0, c_A, N, c_B, N, 0.0, c_C, N);
  
  cloudMemcpy(socket,  C,  c_C,  size * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
  
  cloudTimer.end();    
  double time_in_seconds = cloudTimer.getDurationInSeconds();
  
  printf("Server response %f ms\n", time_in_seconds * 1000);
            
#if 0  
  for (int i = 0 ; i < N ; i++)
    for (int j = 0; j < N; j++) {
      double sum = 0;
      for (int k = 0; k < N; k++)
	sum += A[i * N + k] * B[k * N + j];
      C_ref[i * N + j] = sum;
  }
#endif  

#if 0  
  cloudTimer.start();
  for (int i = 0 ; i < N ; i++)
    for (int j = 0; j < N; j++) {
      double sum = 0;
      for (int k = 0; k < N; k++)
	sum += A[k * N + i] * B[j * N + k];
      C_ref[j * N + i] = sum;
  }
  cloudTimer.end();    
  time_in_seconds = cloudTimer.getDurationInSeconds();
  
  printf("Naive implementation %f ms\n", time_in_seconds*1000);
  int count = 0;
  int ferror = 0;
  for (int i = 0; i < size ; i++)
     if (fabs(C[i] - C_ref[i]) >  EPSILON) {
       ferror =1;
       if (count <10){
	  count ++;
	  printf("%d %f %f\n",i,  C_ref[i], C[i]);
       }

     }
  if (ferror ==0)
     printf("Passed\n");
  else
     printf("Failed\n");      
#endif  
#if 0
  printf("A:\n");
  for (int i = 0 ; i < N ; i++){
    for (int j = 0; j < N; j++) 
      printf("%f ", A[i * N + j]);
    printf("\n");
  }
  
  printf("B:\n");
  for (int i = 0 ; i < N ; i++){
    for (int j = 0; j < N; j++) 
      printf("%f ", B[i * N + j]);
    printf("\n");
  }
  
  printf("C:\n");
  for (int i = 0 ; i < N ; i++){
    for (int j = 0; j < N; j++) 
      printf("%f ", C[i * N + j]);
    printf("\n");
  }
  
  printf("C_ref:\n");
  for (int i = 0 ; i < N ; i++){
    for (int j = 0; j < N; j++) 
      printf("%f ", C_ref[i * N + j]);
    printf("\n");
  }
#endif  

  free(A);
  free(B);
  free(C);
  free(C_ref);
  cloudFree(socket, c_A);
  cloudFree(socket, c_B);
  cloudFree(socket, c_C);
  cloudFinish(socket);
  return 0;
}
