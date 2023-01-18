#ifndef CLIENTACCEPT_H
#define CLIENTACCEPT_H

int MakeSocket(char *host, char *port);

void WriteDataToFile(char *path_name, char *data, int file_size);

void AcceptFile(int sfd);

#endif
