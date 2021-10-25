#include "server_manager.h"

int get_auth_details(int socekt, char* field, int field_size);
int find_client(char* username, char* password, user *users, int max_users);
int login_client(int socket, user* users);
int answer_requests(user* users, int index, char* courses_file_path);
int collect_live_sockets(int *waiting, user *users, int size, fd_set *fds, int listening_socket);
int find_first_empty_cell(int *array, int size);
void answer_clients(user *users, int size, fd_set *fds, char *files_path)
void login_new_clients(int *waiting, user *users, fd_set *fds, int size);
void accept_new_connection(int *waiting_array, int socket, fd_set *fds, int empty_cell);

int get_auth_details(int socekt, char* field, int field_size)
{
	short length;
	if (transfer_all(socket, (char *)&length, 2, 'r') < 0)
	{
		return -1;
	}
	length = ntohs(length);
	while (length > 0)
	{
		int tmp;
		tmp = length < field_size ? length : field_size - 1;
		if (transfer_all(socket, field, tmp, 'r') < 0)
		{
			return -1;
		}
		field[tmp + 1] = 0;
		length -= tmp;
	}
	return 1;
}

int find_client(char* client_username, char* client_password, user* users, int max_users) {
	int i;
	for (i = 0; i < max_users; i++) {
		if (strcmp(client_username, (users[i]).name) == 0) {
			if (strcmp(client_password, (users[i]).password) == 0) {
				if (users[i].socket_fd < 0){
					return i;
				}
				return -1;
			}
		}
	}
    return -1;
}

int login_client(int socket, user* users)
{
	int client_found;
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
    char answer;
	
	if(get_auth_details(socket, username, MAX_NAME_LENGTH) < 0)
	{
		return -1;
	}
	if(get_auth_details(socket, password, MAX_NAME_LENGTH) < 0)
	{
		return -1;
	}
    
	client_found = find_client(username, password, users, MAX_CLIENTS);//server_utils
	if (client_found >= 0)
	{
    	users[client_found].socket_fd = socket;
		answer = 1;
	} 
	else 
	{
		answer = 0;
	}
	if(transfer_all(socket, &answer, 1, 's') < 0)
	{
		return -1;
	}
	/*0-not found, -1-connection closed, 1-found*/
    return (int)answer; //to seker_server
}

int answer_requests(user* users, int index, char* courses_file_path) 
{
    char command_code, full_path[MAX_FILE_PATH], course_number[COURSE_NUMBER_LENGTH];
	strncpy(full_path, courses_file_path, strlen(courses_file_path));
	strcat(full_path, "/");
	if(transfer_all(users[index].socket_fd, &command_code, 1, 'r') < 0){
		return -1;
	}
	if (0 == command_code) /* quit command */ 
	{
		return -1;
	}
	if (1 == command_code) /* list_of_courses command */ 
	{
		strcat(full_path, "list_of_courses.txt");
		return send_file(users[index].socket_fd, full_path);
	}
	if (2 == command_code) /* add_course command */ 
	{
		return add_course(users[index].socket_fd, courses_file_path, users, MAX_CLIENTS); //server_parser
	}
	if (3 == command_code) /* rate_course command */ 
	{
		return rate_course(users[index].socket_fd, courses_file_path, users[index].name); //server_parser
	}
	if (4 == command_code) /* get_rate command */ 
	{
		if (get_auth_details(users[index].socket_fd, course_number, COURSE_NUMBER_LENGTH) < 0)
		{
			return -1
		}
		strcat(full_path, course_number);
		return send_file(users[index].socket_fd, full_path);
	}
	if (5 == command_code) /* get_rate command */ 
	{
		return broadcast_command(users, index, MAX_CLIENTS); //server_parser
	}
    return -1;
}

void handle_clients(int socket, user *users, char * courses_files_path)
{
	int i, max, first_empty_cell, waiting[MAX_CLIENTS];
	fd_set read_fds;
	for (i = 0; i < MAX_CLIENTS; i++){
		waiting[i] = -1;
	}
	while (1)
	{
		first_empty_cell = find_first_empty_cell(waiting, MAX_CLIENTS);
		max = collect_live_sockets(waiting, users, MAX_CLIENTS, &read_fds, socket);

		select(max + 1, &read_fds, NULL, NULL, NULL);
		answer_clients(users, MAX_CLIENTS, &read_fds, courses_files_path);
		login_new_clients(waiting, users, &read_fds, MAX_CLIENTS);
		accept_new_connection(waiting, socket, &read_fds, first_empty_cell);
	}
}

int collect_live_sockets(int *waiting, user *users, int size, fd_set *fds, int listening_socket)
{
	int i, max;
	max = listening_socket;
	FD_ZERO(fds);
	FD_SET(listening_socket, fds);
	for (i = 0; i < size; i++){
		if (waiting[i] > 0){
			FD_SET(waiting[i], fds);
			max = max < waiting[i] ? waiting[i] : max;
		}
		if (users[i].socket_fd > 0){
			FD_SET(users[i].socket_fd, fds);
			max = max < users[i].socket_fd ? users[i].socket_fd : max;
		}
	}
	return max;
}

int find_first_empty_cell(int *array, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (array[i] < 0)
		{
			return i;
		}
	}
	return -1;
}

void answer_clients(user *users, int size, fd_set *fds, char *files_path)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (FD_ISSET(users[i].socket_fd, fds))
		{
			if (answer_requests(users, i, files_path) < 0)
			{
				close(users[i].socket_fd);
				users[i].socket_fd = -1;
			}
		}
	}
}
void login_new_clients(int *waiting, user *users, fd_set *fds, int size)
{
	int i, login_answer;
	for (i = 0; i < size; i++)
	{
		login_answer = 0;
		if (FD_ISSET(waiting[i], fds))
		{
			login_answer = login_client(waiting[i], users);
		}
		if (login_answer != 0)
		{
			if (login_answer < 0)
			{
				close(waiting[i]);
			}
			waiting[i] = -1;
		}
	}
}

void accept_new_connection(int *waiting_array, int socket, fd_set *fds, int empty_cell)
{
	if (empty_cell < 0)
	{
		return;
	}
	if (FD_ISSET(socket, fds))
	{
		waiting_array[empty_cell] = accept(socket, (struct sockaddr*)0, 0));
	}
}
