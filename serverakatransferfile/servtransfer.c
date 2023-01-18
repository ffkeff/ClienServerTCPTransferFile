#include "servtransfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

char* ReadFromFile(char* path_name, int file_size){
 
    printf("[ OK ]\tStart reading from file %s\n", path_name);
    FILE* fin = fopen(path_name, "r");
    if (fin == NULL){
            perror("Error opening file\n");
            exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish opening\n");
    char* buffer = (char*)malloc(file_size);
    size_t retval;
    if ((retval = fread(buffer, sizeof(char), file_size, fin)) != strlen(buffer)){
        fprintf(stderr, "fread() failed: %zu\n", retval);
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish reading\n");
    return buffer;
}

int FileSize(char* path_name){
 
    struct stat st;
    stat(path_name, &st);
    int file_size = st.st_size;
    return file_size;
}

int StartServ(){

    printf("[ OK ]\tStart opening connection\n");
    int sfd;
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Error opening socket\n");   
        return 1;
    }
    struct sockaddr_in adr;
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(7777);
    bind(sfd, (struct sockaddr*) &adr, sizeof(adr));
    listen(sfd, 1);
    socklen_t l_adr = sizeof(adr);
    int fd;
    if ((fd = accept(sfd, (struct sockaddr*) &adr, &l_adr)) == -1){
        perror("Accept is failed\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish opening connection\n");
    return fd;
}

void TransferFileData(char* file_name, char* file_data, int file_size, int fd){
 
    printf("[ OK ]\tStart send information\n");
    int sd;
    if ((sd = send(fd, file_name, 32, 0)) == -1){
        perror("Send file header failed\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tSend: %d bytes\n", sd);
    int* p = &file_size;
    if ((sd = send(fd, p, 32, 0)) == -1){
        perror("Send file header failed\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish transfer file header\n");
    printf("[ OK ]\tFinish send file size: %d\n", *p);
    if ((sd = send(fd, file_data, strlen(file_data), 0)) == -1){
        perror("Send file data failed\n");
        exit(EXIT_FAILURE);
    }
    printf("[ OK ]\tFinish transfer file data\n");
}

