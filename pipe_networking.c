#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  if (mkfifo(WKP, 0666) == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("Named fifo created\n");
  printf("Opened wkp\n");
  int from_client = open(WKP, O_RDONLY);
  printf("Connected\n");
  if (unlink(WKP) == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
    int from_client = server_setup();
    //read SYN
    int syn;
    read(from_client, &syn, sizeof(int));
    printf("Server reading SYN: %d\n", syn);
    return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    int pid = getpid();
    char *PP;
    sprintf(PP, "%d", pid);
    if (mkfifo(PP, 0666) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    *to_server = open(WKP, O_WRONLY);
    if (*to_server == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    write(*to_server, &pid, sizeof(int));
    printf("Client: Opening PP\n");
    int downstream = open(PP, O_RDONLY);
    printf("Client: connected to PP\n");
    return 0;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


