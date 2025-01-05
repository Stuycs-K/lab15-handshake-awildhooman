basic: client basic_server
persistent: client persistent_server
forking: client forking_server

client: basic_client.o pipe_networking.o
	@gcc -o client basic_client.o pipe_networking.o

basic_server: basic_server.o pipe_networking.o
	@gcc -o server basic_server.o pipe_networking.o

persistent_server: persistent_server.o pipe_networking.o
	@gcc -o server persistent_server.o pipe_networking.o

forking_server: forking_server.o pipe_networking.o
	@gcc -o server forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

clean:
	@rm -f *.o server client
