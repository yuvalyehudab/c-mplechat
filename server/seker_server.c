#include "seker_server.h"

int main(int argc, char* argv[]) {
    int listening_socket, port;
    user users[MAX_CLIENTS];

	if (validate_arguments(argc, argv) < 0)
	{
		return -1;
	}
	//load_users_from_file
    if(load_users_from_file(argv[1], users, MAX_CLIENTS) < 0)
	{
		return -1;
	}
	port = (argc > 3) ? strtol(argv[3], NULL, 10) : DEFAULT_PORT;

    listening_socket = create_listening_socket(port); //server_create_sockets
	if (listening_socket < 0)
	{
		return -1;
	}
	
	handle_clients(listening_socket, users, argv[2]);//server_manager
    return 0;
}
