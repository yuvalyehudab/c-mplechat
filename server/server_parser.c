#include "server_parser.h"

int add_course(int client_socket, char* courses_file_path, user *users, int size) {
	char course_number[COURSE_NUMBER_LENGTH], line[LINE_SIZE];
	char course_description[MAX_COURSE_DESCRIPTION];
	char* existing_course;
	char full_path[MAX_FILE_PATH];// courses_list_path[MAX_FILE_PATH];
	FILE* fp;
	short s;
	char answer[LINE_SIZE];
	int max, i;
	fd_set write_fds;
	strcpy(full_path, courses_file_path);
	strcat(full_path, "/");
	strcat(full_path, "list_of_courses.txt");
	if (get_course_info(client_socket, course_number) < 0){ //server_utils // Get course number
		return -1;
	}
	if(get_course_info(client_socket, course_description) < 0){ //server_utils // Get course description
		return -1;
	}

	fp = fopen(full_path, "a+");
	if (fp == NULL) {
		perror("File opening error");
		return -1;
	}
	strcpy(answer, course_number);
	while (fgets(line, LINE_SIZE, fp) != NULL){
		existing_course = strtok(line, " :\t");
		if (existing_course != NULL && strcmp(existing_course, course_number) == 0){/* course already exists */
			fclose(fp);
			strcat(answer, " exists in the database!\n");
			s = htons((short)strlen(answer));
			transfer_all(client_socket, (char *)&s, 2, 's');
			return transfer_all(client_socket, answer, strlen(answer), 's'); //full_connection
		}
	}
	fprintf(fp, "%s:\t\"%s\"\n", course_number, course_description);
	fclose(fp);
	//fprintf(stderr, "in file: %s:\t\"%s\"\n", course_number, course_description);
	//printf("s: %d\tanswer: %s\tlen:%ld\n", s, answer, strlen(answer));
	full_path[strlen(full_path) - strlen("list_of_courses.txt")] = 0;
	strcat(full_path, course_number);
	fp = fopen(full_path, "a+"); /*create rates file*/
	fclose(fp);
	/* course was added */
	line[0] = '\0';
	strcpy(line, "A new course was just added!\n");
	if (broadcast(line, users, size, client_socket) < 0)
	{
		return -1;
	}
	strcat(answer, " added successfully.\n");
	s = htons((short)strlen(answer));
	transfer_all(client_socket, (char*)&s, 2, 's');
	transfer_all(client_socket, answer, strlen(answer), 's');
	return 1;
}

int rate_course(int client_socket, char* courses_file_path, char* client_username) {
	FILE* fp;
	char full_path[MAX_FILE_PATH];
	char course_number[COURSE_NUMBER_LENGTH], rating_value[COURSE_RATING_VALUE], rating_text[MAX_COURSE_DESCRIPTION];
	strcpy(full_path, courses_file_path);
	strcat(full_path, "/");

	if (get_course_info(client_socket, course_number) < 0){ //server_utils
		return -1;
	}
	if (get_course_info(client_socket, rating_value) < 0){ //server_utils
		return -1;
	}
	if (get_course_info(client_socket, rating_text) < 0){ //server_utils
		return -1;
	}
	strcat(full_path, course_number);

	fp = fopen(full_path, "r");
	if (fp == NULL){
		return 0;
	}
	fclose(fp);
	fp = fopen(full_path, "a+");
	if (fp == NULL){
		return 0;
	}
	fprintf(fp, "%s:\t%s\t\"%s\"\n", client_username, rating_value, rating_text);
	fclose(fp);
	return 0;
}

int broadcast_command(user *users, int index, int size){
	char message[MAX_BROADCAST_MESSAGE];
	strcpy(message, users[index].name);
	strcat(message, " sent a new message: ");
	if (get_course_info(users[index].socket_fd, (message + strlen(message))) < 0){ //server_utils
		return -1;
	}
	strcat(message, "\n");
	return broadcast(message, users, size, index);
}

int broadcast(char *message, user *users, int size, int index)
{
	int i, max;
	short s;
	fd_set write_fds;
	max = 0;
	FD_ZERO(&write_fds);
	for (i = 0; i < size; i++)
	{
		if (users[i].socket_fd > 0)
		{
			FD_SET(users[i].socket_fd, &write_fds);
			max = max < users[i].socket_fd ? users[i].socket_fd : max;
		}
	}
	select(max + 1, NULL, &write_fds, NULL, NULL);
	for (i = 0; i < size; i++)
	{
		if (i == index)
		{
			continue;
		}
		if (users[i].socket_fd > 0 && FD_ISSET(users[i].socket_fd, &write_fds))
		{
			s = htons((short)strlen(message));
			if (transfer_all(users[i].socket_fd, (char*)&s, 2, 's') < 0)
			{
				return -1;
			}
			if (transfer_all(users[i].socket_fd, message, strlen(message), 's') < 0)
			{
				return -1;
			}
		}
	}
	return 0;
}
