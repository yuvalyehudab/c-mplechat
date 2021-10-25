#ifndef LOAD_USERS_FROM_FILE_H
#define LOAD_USERS_FROM_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "user.h"

int load_users_from_file(char* file_name, user* users, int size);

#endif