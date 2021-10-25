#ifndef SERVER_CREATE_SOCKETS_
#define SERVER_CREATE_SOCKETS_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> //Sockets
#include <netinet/in.h> //Internet addresses
#include <arpa/inet.h> //Working with Internet addresses
#include <netdb.h> //Domain Name Service (DNS)
#include <errno.h> //Working with errno to report errors
#include <string.h>

#define Q_LEN 16

int create_listening_socket(short port);
int create_client_socket(int listening_socket);

#endif 
