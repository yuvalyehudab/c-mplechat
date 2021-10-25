#ifndef FULL_CONNECTION_H_
#define FULL_CONNECTION_H_

#include <sys/socket.h> //Sockets
#include <netinet/in.h> //Internet addresses
#include <arpa/inet.h> //Working with Internet addresses
#include <netdb.h> //Domain Name Service (DNS)
#include <errno.h> //Working with errno to report errors
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int transfer_all(int socket, char *buffer, int length, char direction); /* send or receive length bytes of data,
according to direction (s for send, r for receive) */

#endif
