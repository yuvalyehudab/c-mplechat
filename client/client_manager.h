#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../common/full_connection.h"
#include "get_push_message.h"

#define MESSAGE_LENGTH 4096
#define FIELD_LENGTH 32
#define STDIN 0

int client_login(int socket);
void run_requests(int socket);

#endif
