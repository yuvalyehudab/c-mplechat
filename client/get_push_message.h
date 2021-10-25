//get_push_message.h
#ifndef GET_PUSH_MESSAGE_H
#define GET_PUSH_MESSAGE_H

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define STDIN 0

int get_push_message(int socket, int waiting_for_answer);

#endif
