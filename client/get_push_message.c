//get_push_message.c

#include "get_push_message.h"

int get_push_message(int socket, int waiting_for_answer){
	fd_set read_fds;
	
	FD_ZERO(&read_fds);
	/*when waiting to data from server, don't read commands from client*/
	if (waiting_for_answer == 0){
		FD_SET(STDIN, &read_fds);
	}
	FD_SET(socket, &read_fds);
	
	select(socket + 1, &read_fds, NULL, NULL, NULL);
	
	if (FD_ISSET(socket, &read_fds)){
		/*selet returned, there is data to read in socket*/
		return 1;
	}
	/*select returned and no data to read in socket*/
	return 0;
}