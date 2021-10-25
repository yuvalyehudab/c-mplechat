#include "load_users_from_file.h"

int load_users_from_file(char* file_name, user* users, int size)
{
	FILE *fp;
	int i, bytes_read;

	if (file_name == NULL)
	{
		return -1;
	}
	for (i = 0; i < size; ++i)
	{
		users[i].socket_fd = -1;
	}
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		return -1;
	}
	clearerr(fp);
	while (!feof(fp) && !ferror(fp))
	{
		fscanf(fp, "%s\t%s", users[i].name, users[i].password);
		i++;
	}
	fclose(fp);
	return 0;
}
