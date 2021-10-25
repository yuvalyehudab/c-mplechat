#include "full_connection.h"

int transfer_all(int socket, char *buffer, int length, char direction) {
	int total, bytes_left, n;
	total = 0;
	bytes_left = length;
	while (total < length) {
        if (direction == 's'){//printf("sent: %s\n", buffer);
			n = send(socket, buffer + total, bytes_left, 0);//printf("send unblocks on socket\n");
		} else{//printf("recv blocks on socket: %d\n", socket);
			n = recv(socket, buffer + total, bytes_left, 0);//printf("received: %s\n", buffer);
		}
		if (n < 1 && length != 0) {
			return -1;
		}
		total += n;
		bytes_left -= n;
	}
	return bytes_left; //should be 0 if all sent/received successfully
}
