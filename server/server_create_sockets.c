#include "server_create_sockets.h"

int create_listening_socket(short port)
{
    int socketfd;
    struct sockaddr_in server;
    if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socketfd, (struct sockaddr*)&server, sizeof(server))) 
	{
    	close(socketfd);
		return -2;
	}
	if (listen(socketfd, Q_LEN) < 0)
	{
	    close(socketfd);
		return -3;
	}
    return socketfd;
}
