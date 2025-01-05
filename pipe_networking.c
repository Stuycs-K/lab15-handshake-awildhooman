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
    if (access(WKP, F_OK) == 0) {
        if (unlink(WKP) == -1) {
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        printf("Removed existing WKP\n");
    }
    if (mkfifo(WKP, 0666) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Created WKP\n");
    printf("Server opening WKP\n");
    int from_client = open(WKP, O_RDONLY);
    if (from_client == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Server connected to WKP\n");
    if (unlink(WKP) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Server removed WKP\n");
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
    char downstream[HANDSHAKE_BUFFER_SIZE];
    read(from_client, &downstream, HANDSHAKE_BUFFER_SIZE);

    *to_client = open(downstream, O_WRONLY);
    srand(time(NULL));
    int SYN_ACK = rand();
    write(*to_client, &SYN_ACK, sizeof(int));

    int ACK;
    read(from_client, &ACK, sizeof(int));
    if (ACK != SYN_ACK + 1) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    printf("Server handshake successful\n");
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
    char PP[HANDSHAKE_BUFFER_SIZE];
    sprintf(PP, "%d", getpid());
    if (access(PP, F_OK) == 0) {
        if (unlink(PP) == -1) {
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        printf("Removed existing PP\n");
    }
    if (mkfifo(PP, 0666) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Client created PP\n");
    *to_server = open(WKP, O_WRONLY);
    printf("Client connected to WKP\n");
    write(*to_server, PP, HANDSHAKE_BUFFER_SIZE);
    printf("Client send PP name to server\n");
    int downstream = open(PP, O_RDONLY);
    printf("Client connected to PP\n");
    int SYN_ACK;
    read(downstream, &SYN_ACK, sizeof(int));
    if (unlink(PP) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Client removed PP\n");
    int ACK = SYN_ACK + 1;
    write(*to_server, &ACK, sizeof(int));
    printf("Client handshake successful\n");
    return downstream;
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


