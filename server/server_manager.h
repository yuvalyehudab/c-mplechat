#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "user.h"
#include "../common/full_connection.h"
#include "server_parser.h"

#define MAX_FILE_PATH 1024
#define MAX_COURSE_DESCRIPTION 2048
#define COURSE_NUMBER_LENGTH 8
#define COURSE_RATING_VALUE 4

void handle_clients(int socket, user *users, char * courses_files_path);

#endif
