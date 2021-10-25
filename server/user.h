#ifndef USER_H_
#define USER_H_

#define MAX_NAME_LENGTH 16
#define MAX_CLIENTS 32

struct user {
	char name[MAX_NAME_LENGTH];
	char password[MAX_NAME_LENGTH];
	int socket_fd;
};
typedef struct user user;

#endif