#ifndef SERVTRANSFER_H
#define SERVTRANSFER_H

char* ReadFromFile(char* path_name, int file_size);

int FileSize(char* path_name);

int StartServ();

void TransferFileData(char* file_name, char* file_data, int file_size, int fd);

#endif
