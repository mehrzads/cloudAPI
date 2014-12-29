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
    cloudInit(portno, hostname, sockfd);

    int size = 8192 * 8192 ;
    float * A = (float *) malloc( size * sizeof(float));
    float * B = (float *) malloc( size * sizeof(float));
    cloudMalloc(sockfd, (void **)&c_A, size * sizeof(float));
      
    for (int i = 0; i < size; i++){
	A[i] = float(rand())/INT_MAX;
     }

    auto start_time = std::chrono::steady_clock::now();
    cloudMemcpy(sockfd,  c_A,  A,  size * sizeof(float), cloudMemcpyClientToCloud, true);
    cloudMemcpy(sockfd,  B,  c_A,  size * sizeof(float), cloudMemcpyCloudToClient, true);
    double time_in_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - start_time).count() / 1000.0;
    
    printf("Transfer from server %f ms\n", time_in_seconds * 1000);
    printf("Transfer rate %f Gbps\n", (size * sizeof(float) * 8 * 2 )/(1024 * 1024 *1024 *time_in_seconds) );
	      
      
      
    int ferror = 0;
    for (int i = 0; i < size ; i++)
       if (A[i] != B[i])
         ferror =1;
    if (ferror ==0)
       printf("Passed\n");
    else
       printf("Failed\n");       

    free(A);
    free(B);
    cloudFree(sockfd, c_A);
    cloudFinish(sockfd);
    return 0;
}
