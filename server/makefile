
CC = gcc-8.3.0
SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o)

EXEC = seker_server
COMP_FLAG = -Wall -Werror -pedantic-errors -Wextra -O3 -std=gnu99

debug: COMP_FLAG += -g -pg -DDEBUG
debug: $(EXEC)
	#Debug: seker_server users_file files_path [port], ex: seker_server users.txt ./data 5020, seker_server users.txt . 5020

all: $(EXEC)
	#Compiled!

seker_server: $(OBJS) full_connection.o
	$(CC) $(COMP_FLAG) -o $@ $^

seker_server.o: seker_server.c seker_server.h load_users_from_file.o server_create_sockets.o server_manager.o user.h
	$(CC) $(COMP_FLAG) -c $<

server_manager.o: server_manager.c server_manager.h server_parser.o full_connection.o user.h
	$(CC) $(COMP_FLAG) -c $<

server_parser.o: server_parser.c server_parser.h server_utils.o full_connection.o user.h
	$(CC) $(COMP_FLAG) -c $<

server_utils.o: server_utils.c server_utils.h full_connection.o user.h
	$(CC) $(COMP_FLAG) -c $<

load_users_from_file.o: load_users_from_file.c load_users_from_file.h user.h
	$(CC) $(COMP_FLAG) -c $<

server_create_sockets.o: server_create_sockets.c server_create_sockets.h
	$(CC) $(COMP_FLAG) -c $<
	
full_connection.o: ../common/full_connection.c ../common/full_connection.h
	$(CC) $(COMP_FLAG) -c $<

clean:
	rm -f *.o $(EXEC)

#DEBUG:
#profiler-gprof, valgrind, gdb
#valgrind-3.14.0 -v --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all
