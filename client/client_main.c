#include "client_main.h" /* TODO what if connection aborted in the middle of a function? TODO free()/close() TODO fix strtok TODO run tests*/

int main (int argc, char *argv[]) 
{
    int socketfd, port;
    char hostname[HOSTNAME_SIZE] = DEFAULT_HOST;
    port = DEFAULT_PORT;
    if (argc > 1)
    {
        if (argc > 2)
        {
            port = atoi(argv[2]);
        }
        strncpy(hostname, argv[1], HOSTNAME_SIZE);
    }
    if ((socketfd = client_connection(hostname, port)) < 0) //client_connection
    {
        return -1;
    }
	
    if (client_login(socketfd) < 0) //client_manager
    {
		close_connection(socketfd); //client_connection
		return -1;
	}
    run_requests(socketfd);//client_manager
    close_connection(socketfd); //client_connection
    return 0;
}