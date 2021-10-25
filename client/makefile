
CC = gcc-8.3.0
SRC := $(wildcard *.c)
OBJS := $(SRC:.c=.o)

EXEC = seker_client
COMP_FLAG = -Wall -Werror -pedantic-errors -Wextra -O3 -std=gnu99

debug: COMP_FLAG += -g -pg -DDEBUG
debug: $(EXEC)
	#Debug: seker_client [host [port]], ex: seker_client localhost 5020, seker_client 127.0.0.1 4040

all: $(EXEC)
	#Compiled!

seker_client: $(OBJS) full_connection.o
	$(CC) $(COMP_FLAG) -o $@ $^

client_main.o: client_main.c client_main.h client_connection.o client_manager.o
	$(CC) $(COMP_FLAG) -c $<

client_connection.o: client_connection.c client_connection.h
	$(CC) $(COMP_FLAG) -c $<

client_manager.o: client_manager.c client_manager.h full_connection.o get_push_message.o
	$(CC) $(COMP_FLAG) -c $<

get_push_message.o: get_push_message.c get_push_message.h
	$(CC) $(COMP_FLAG) -c $<
	
full_connection.o: ../common/full_connection.c ../common/full_connection.h
	$(CC) $(COMP_FLAG) -c $<

clean:
	rm -f *.o $(EXEC)

#DEBUG:
#profiler-gprof, valgrind, gdb
#valgrind-3.14.0 -v --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all
