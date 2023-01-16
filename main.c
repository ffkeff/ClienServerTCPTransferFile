#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "servtransfer.h"

int main(int argc, char* argv[]){
 
    if (argc != 2){
        printf("Error args! Usage: Start <filename>\n");
        return 1;
    }
    char* file_data = ReadFromFile(argv[1], FileSize(argv[1]));
    int fd = StartServ();
    int file_data_size = strlen(file_data);
    printf("filedatasize %d\n", file_data_size);
    TransferFileData(argv[1], file_data, file_data_size, fd);
    return 0;
}
