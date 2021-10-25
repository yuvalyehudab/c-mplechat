#profiler, valgrind
CC = gcc-8.3.0
OBJS = *.o
EXEC = seker_client seker_server
COMP_FLAG = -Wall -g -pg -Werror -pedantic-errors -Wextra -O3 -std=gnu99
CLIENT_SRC = seker_client.o client_connection.o client_manager.o client_parser.o full_connection.o get_push_message.o
SERVER_SRC = seker_server.o seker_server.o load_users_from_file.o server_create_sockets.o server_manager.o full_connection.o server_parser.o server_utils.o

all: $(EXEC)
	#Compiled!

seker_client: $(CLIENT_SRC)
	$(CC) $(COMP_FLAG) -o $@ $^

seker_server: $(SERVER_SRC)
	$(CC) $(COMP_FLAG) -o $@ $^

seker_client.o: seker_client.c seker_client.h client_connection.o client_manager.o
	$(CC) $(COMP_FLAG) -c $<

client_connection.o: client_connection.c client_connection.h
	$(CC) $(COMP_FLAG) -c $<

client_manager.o: client_manager.c client_manager.h client_parser.o full_connection.o get_push_message.o
	$(CC) $(COMP_FLAG) -c $<

client_parser.o: client_parser.c client_parser.h full_connection.o
	$(CC) $(COMP_FLAG) -c $<

get_push_message.o: get_push_message.c get_push_message.h
	$(CC) $(COMP_FLAG) -c $<
	
full_connection.o: full_connection.c full_connection.h
	$(CC) $(COMP_FLAG) -c $<

seker_server.o: seker_server.c seker_server.h load_users_from_file.o server_create_sockets.o server_manager.o user.h
	$(CC) $(COMP_FLAG) -c $<

load_users_from_file.o: load_users_from_file.c load_users_from_file.h
	$(CC) $(COMP_FLAG) -c $<

server_create_sockets.o: server_create_sockets.c server_create_sockets.h
	$(CC) $(COMP_FLAG) -c $<
	
server_manager.o: server_manager.c server_manager.h full_connection.o server_parser.o user.h
	$(CC) $(COMP_FLAG) -c $<

server_parser.o: server_parser.c server_parser.h server_utils.o full_connection.o user.h
	$(CC) $(COMP_FLAG) -c $<

server_utils.o: server_utils.c server_utils.h full_connection.o user.h
	$(CC) $(COMP_FLAG) -c $<

clean:
	rm -f $(OBJS) $(EXEC)
