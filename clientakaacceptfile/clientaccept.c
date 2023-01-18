#include "clientaccept.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

int MakeSocket(char *host, char *port){

    int sock, retVal;
    struct addrinfo hints = {
	.ai_family = AF_INET,
	.ai_socktype = SOCK_STREAM,
        .ai_protocol = 0
    }, *servInfo, *p;

    if (0 != (retVal = getaddrinfo(host, port, &hints, &servInfo))){
        fprintf(stderr, "getaddrinfo %s\n", gai_strerror(retVal));
        exit(EXIT_FAILURE);
    }

    for(p = servInfo; p != NULL; p->ai_next){
        if(-1 == (sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol))){
            close(sock);
            continue;
        }

        if(-1 == connect(sock, p->ai_addr, p->ai_addrlen)){
            close(sock);
            continue;
        }
        break;
    }
    return sock;
}

void WriteDataToFile(char *path_name, char *data, int file_size){

    FILE *fout;
    if (NULL == (fout = fopen(path_name, "w"))){
        fprintf(stderr, "fopen() failed\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(data) != fwrite(data, sizeof(char), file_size, fout)){
        fprintf(stderr, "fwrite() failed\n");
        exit(EXIT_FAILURE);
    }
}

void AcceptFile(int sock){

    int retval;
    char *file_name = (char*)malloc(32);
    int *file_size  = (int*)malloc(32);
    if ((retval = recv(sock, file_name, 32, 0)) == -1){
        perror("Error recv filename\n");
        exit(EXIT_FAILURE);
    }

    if ((retval = recv(sock, file_size, 32, 0)) == -1){
        perror("Error recv file size\n");
        exit(EXIT_FAILURE);
    }

    char *file_data = (char*)malloc(*file_size);
    if ((retval = recv(sock, file_data, *file_size, 0)) == -1){
        perror("Error recv file size\n");
        exit(EXIT_FAILURE);
    }
    WriteDataToFile(file_name, file_data, *file_size);
}
