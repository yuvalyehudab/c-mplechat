#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "user.h"
#include "server_utils.h"
#include "../common/full_connection.h"

#define MAX_FILE_PATH 1024
#define MAX_COURSE_DESCRIPTION 2048
#define COURSE_NUMBER_LENGTH 8
#define COURSE_RATING_VALUE 4
#define LINE_SIZE 128
#define MAX_BROADCAST_MESSAGE 256

int send_list_of_courses(int client_socket, char* courses_file_path);
int add_course(int client_socket, char* courses_file_path, user *users, int size);
int rate_course(int client_socket, char* courses_file_path, char* client_username);
int get_rate(int client_socket, char* courses_file_path);
int broadcast_command(user *users, int index, int size);

#endif // SERVER_PARSER_H
