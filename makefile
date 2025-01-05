basic: basic_client basic_server
persistent: basic_client persistent_server
forking: basic_client forking_server
compile: forking

basic_client Client: basic_client.o pipe_networking.o
	@gcc -o client_ basic_client.o pipe_networking.o

basic_server: basic_server.o pipe_networking.o
	@gcc -o server_ basic_server.o pipe_networking.o

persistent_server: persistent_server.o pipe_networking.o
	@gcc -o server_ persistent_server.o pipe_networking.o

forking_server: forking_server.o pipe_networking.o
	@gcc -o server_ forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

server: server_
	@./server_

client: client_
	@./client_

clean:
	@rm -f *.o server_ client_
