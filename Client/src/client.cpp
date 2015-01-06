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

    float * c_A;
    float * c_B;
    float * c_C;
    cloudInit(portno, hostname, sockfd);
    int N = 1024;
    int size = N * N;
    float * A = (float *) malloc( size * sizeof(float));
    float * B = (float *) malloc( size * sizeof(float));
    float * C = (float *) malloc( size * sizeof(float));
    float * C_ref = (float *) malloc( size * sizeof(float));
    cloudMalloc(sockfd, (void **)&c_A, size * sizeof(float));
    cloudMalloc(sockfd, (void **)&c_B, size * sizeof(float));
    cloudMalloc(sockfd, (void **)&c_C, size * sizeof(float));
      
    for (int i = 0; i < size; i++){
	A[i] = float(rand())/INT_MAX;
	B[i] = float(rand())/INT_MAX;
	C_ref[i] = 0;
	C[i] = 0;
     }

    auto start_time = std::chrono::steady_clock::now();
    cloudMemcpy(sockfd,  c_A,  A,  size * sizeof(float), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
    cloudMemcpy(sockfd,  c_B,  B,  size * sizeof(float), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
    matrixMultiply(sockfd, N, N, N , c_A, c_B, c_C);
    
    cloudMemcpy(sockfd,  C,  c_C,  size * sizeof(float), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
    double time_in_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - start_time).count() / 1000.0;
    
    printf("Transfer from server %f ms\n", time_in_seconds * 1000);
    printf("Transfer rate %f Gbps\n", (size * sizeof(float) * 8 * 2 )/(1024 * 1024 *1024 *time_in_seconds) );
	      
    
  for (int i = 0 ; i < N ; i++)
    for (int j = 0; j < N; j++) {
      float sum = 0;
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
