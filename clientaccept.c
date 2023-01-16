#include "clientaccept.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int MakeSocket(char* host, int port){
 
    printf("[ OK ]\tStart opening connection\n");
    int cfd;
    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Error open socket\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    int retval;
    if ((retval = inet_pton(AF_INET, host, &adr.sin_addr)) == -1){
        perror("Error inet pton\n");
        exit(EXIT_FAILURE);
    }
    if ((retval = connect(cfd, (struct sockaddr*) &adr, sizeof(adr))) == -1){
        perror("Error connect\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish opening connection\n");
    return cfd;
}

void WriteDataToFile(char* path_name, char* data, int file_size){
 
    printf("[ OK ]\tStart writing data to file\n");
    FILE* fout; 
    if ((fout = fopen(path_name, "w")) == NULL){
        perror("Error file opening to write\n");
        exit(EXIT_FAILURE);
    }
    size_t retval;
    if ((retval = fwrite(data, sizeof(char), file_size, fout)) != strlen(data)){
        fprintf(stderr, "fwrite() failed: %zu\n", retval);
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish writing to file\n");
}

void AcceptFile(int cfd){
 
    printf("[ OK ]\tStart accept file\n");
    int retval;
    char* file_name = (char*)malloc(32);
    int* file_size  = (int*)malloc(32);
    if ((retval = recv(cfd, file_name, 32, 0)) == -1){
        perror("Error recv filename\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish accept file name: %s\n", file_name);
    if ((retval = recv(cfd, file_size, 32, 0)) == -1){
        perror("Error recv file size\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish accept file size: %d\n", *file_size);
    char* file_data = (char*)malloc(*file_size);
    if ((retval = recv(cfd, file_data, *file_size, 0)) == -1){
        perror("Error recv file size\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish accept file data\n");
    printf("[ OK ]\tFinish file accept\n");
    WriteDataToFile(file_name, file_data, *file_size);
} 
