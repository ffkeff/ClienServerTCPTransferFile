#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "clientaccept.h"

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Error args!\nUsage: ./client <host> <port>\n");
        return 1;
    }
    int cfd = MakeSocket(argv[1], argv[2]);
    AcceptFile(cfd);

    return 0;
}
