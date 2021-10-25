#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_

#include <netdb.h>
#include <sys/socket.h> //Sockets
#include <netinet/in.h> //Internet addresses
#include <arpa/inet.h> //Working with Internet addresses
#include <netdb.h> //Domain Name Service (DNS)
#include <errno.h> //Working with errno to report errors
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int client_connection(char* hostname, int port);
void close_connection(int socket);

#endif
