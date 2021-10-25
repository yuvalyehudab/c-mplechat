#include "client_manager.h"

char* get_field(char* field, char* str_to_ignore);
int print_error_message();
int send_command_to_server(int socket);
int print_server_message(int socket, int waiting_code);
int load_on_packet(char *packet, int offset, char *arg);
int login_to_server(int socket, char* username, char* password);

int client_login(int socket)
{
    char input_u[FIELD_LENGTH], input_p[FIELD_LENGTH], *username, *password;
	int success = 0;
	printf("Welcome! Please log in.\n");
	clearerr(stdin);
    do
	{
		username = get_field(input_u, "User:");
		password = get_field(input_p, "Password:");
		success = login_to_server(socket, username, password); //client_parser
    } while(success  == 0 && !feof(stdin) && !ferror(stdin));
	if (success < 0)
	{
		return -1;
	}
    printf("Hi %s, good to see you.\n", username);
	return 0;
}

void run_requests(int socket)
{
	int wait_for_answer;
	wait_for_answer = 0;
	while (wait_for_answer > -1)
	{
		if (get_push_message(socket, wait_for_answer) == 1) //server_sent_data?
		{
			wait_for_answer = print_server_message(socket, wait_for_answer);
		}
		else
		{
			wait_for_answer = send_command_to_server(socket);
		}
	}
}

char* get_field(char* field, char* str_to_ignore)
{
	char* raw;
	if (feof(stdin) || ferror(stdin) || str_to_ignore == NULL || 0 == str_to_ignore[0])
	{
		return NULL;
	}	
	fgets(field, FIELD_LENGTH, stdin);
	if (field == NULL || 0 == field[0])
	{
		return NULL;
	}
	raw = strtok(field, " ");
	if (raw == NULL || strcmp(raw, str_to_ignore) != 0)
	{
		return NULL;
	}
	raw = strtok(NULL, " \r\t\n");
	if (raw == NULL || raw[0] == 0)
	{
		return NULL;
	}
	return raw;
}

int send_command_to_server(int socket)
{
	char raw_command[MESSAGE_LENGTH], ready_packet[MESSAGE_LENGTH], *tmp_ptr, delimiter[FIELD_LENGTH];
	int parameter_amount, waiting_code, packet_length;
	
	fgets(raw_command, MESSAGE_LENGTH, stdin);
	if (feof(stdin) || ferror(stdin))
	{
		return -1;
	}
	strcpy(delimiter, " \t\r\n");
	tmp_ptr = strtok(raw_command, delimiter);
	packet_length = 1;
	if (tmp_ptr == NULL)
	{
		return print_error_message();
	}
	else if (strcmp("list_of_courses", tmp_ptr) == 0)
	{
		ready_packet[0] = 1;
		parameter_amount = 0;
		waiting_code = 2;
	}
	else if (strcmp("add_course", tmp_ptr) == 0)
	{
		ready_packet[0] = 2;
		parameter_amount = 2;
		waiting_code = 1;
	}
	else if (strcmp("rate_course", tmp_ptr) == 0)
	{
		ready_packet[0] = 3;
		parameter_amount = 3;
		waiting_code = 0;
	}
	else if (strcmp("get_rate", tmp_ptr) == 0)
	{
		ready_packet[0] = 4;
		parameter_amount = 1;
		waiting_code = 2;
	}
	else if (strcmp("broadcast", tmp_ptr) == 0)
	{
		ready_packet[0] = 5;
		parameter_amount = 1;
		waiting_code = 0;
	}
	else if (strcmp("quit", tmp_ptr) == 0)
	{
		ready_packet[0] = 0;
		parameter_amount = 0;
		waiting_code = -1;
	}
	else
	{
		return print_error_message();
	}
	while (parameter_amount > 0)
	{
		parameter_amount--;
		if (parameter_amount == 0 && ready_packet[0] != 4)
		{
			strncpy(delimiter, "\"", strlen(delimiter));
		}
		tmp_ptr = strtok(NULL, delimiter);
		if (tmp_ptr == NULL || tmp_ptr[0] == 0)
		{
			return print_error_message();
		}
		packet_length += load_on_packet(ready_packet, packet_length, tmp_ptr);		
	}
	if (transfer_all(socket, ready_packet, packet_length, 's') != 0)
	{
		return -1;
	}
	return waiting_code;
}

int print_error_message()
{
	printf("Illegal command.\n");
	return 0;
}

int print_server_message(int socket, int waiting_code)
{
	short message_length;
	char message[MESSAGE_LENGTH];
	if (transfer_all(socket, (char *)&message_length, 2, 'r') < 0) // full connection
	{
		return -1;
	}
	message_length = ntohs(message_length);
	if (transfer_all(socket, message, message_length, 'r') < 0)
	{
		return -1;
	}
	message[message_length] = '\0';
	printf("%s", message);
	if (waiting_code == 1 || message_length == 0)
	{
		return 0;
	}
	return waiting_code;
}

int login_to_server(int socket, char* username, char* password)
{
	int packet_size;
	char c, message_data[MESSAGE_LENGTH];
	c = 0;
	if(username == NULL || password == NULL){
		printf("Failed to login.\n");
		return 0;
	}
	packet_size = load_on_packet(message_data, 0, username);
	packet_size += load_on_packet(message_data, packet_size, password);
	if (transfer_all(socket, message_data, packet_size, 's') < 0){ //full_connection
		return -1;
	}
	if (transfer_all(socket, &c, 1, 'r') < 0) {//full_connection
		return -1;
	}
	if (c == '\0')
	{
		printf("Failed to login.\n");
	}
	return c;
}

int load_on_packet(char *packet, int offset, char *arg)
{
	uint16_t arg_length;
	arg_length = htons(strlen(arg));
	memcpy((void *)(packet + offset), (void *)&arg_length, 2);
	strncpy(packet + offset + 2, arg, strlen(arg));
	return (strlen(arg) + 2);
}