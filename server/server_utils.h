#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#define PATH_MAX 1024
#define FIELD_LENGTH 32

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h> //Internet addresses
#include <arpa/inet.h> //Working with Internet addresses
#include "user.h"
#include "../common/full_connection.h"

int find_client(char* username, char* password, user *users, int max_users); /* returns client's index in usernames
and passwords, or returns -1 if not found*/
int get_course_info(int socket, char *info_to_receive);
int send_file(int client_socket, char* path);

#endif // SERVER_UTILS_H
