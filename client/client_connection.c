#include "client_connection.h"

int client_connection(char* hostname, int port)
{
	int socketfd;
	struct sockaddr_in server;
	struct hostent *hp;
    hp = gethostbyname(hostname);
    if (hp == NULL)
    {
        perror("Get host by name failed");
        return -1;
    }

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
		return -1;
	}
    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    if (connect(socketfd, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("Connect failed");
        close_connection(socketfd);
        return -1;
    }
    return socketfd;
}

void close_connection(int socketfd)
{
    close(socketfd);
}
