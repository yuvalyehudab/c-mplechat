#include "server_utils.h"

int get_course_info(int socket, char *info_to_receive){
	unsigned short len;
	if (transfer_all(socket, (char*)&len, sizeof(short), 'r') < 0){ //full_connection
		return -1;
	}
	len = ntohs(len);
	if (transfer_all(socket, info_to_receive, len, 'r') < 0){
		return -1;
	}
	info_to_receive[len] = 0;
	return 0;
}

int send_file(int client_socket, char* path){
	FILE *fp;
	char *line;
	/*int offset, bytes_read; //int len;
	size_t bytes_left;*/
	unsigned short unit_len;

	unit_len = 0;
	fp = fopen(path, "r");
	if (fp == NULL){
		return transfer_all(client_socket, (char *)&unit_len, 2, 's');
	}
	clearerr(fp);
	line = fgets(path + 2, PATH_MAX, fp);
	while (!feof(fp) && !ferror(fp) && line != NULL){
		unit_len = htons(strlen(line));
		memcpy(path, (char*)&unit_len, 2);
		if(transfer_all(client_socket, path, strlen(line) + 2, 's') < 0){
			fclose(fp);
			return -1;
		}
		line = fgets(path + 2, PATH_MAX, fp);
	}
	fclose(fp);
	unit_len = 0;
	transfer_all(client_socket, (char *)&unit_len, 2, 's');
	return 1;//transfer_all(client_socket, (char *)&unit_len, 2, 's');
}
