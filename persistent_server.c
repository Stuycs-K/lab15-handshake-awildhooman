#include "pipe_networking.h"

int to_client = -1;
int from_client = -1;
int connected = 0;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (to_client != -1) {
            close(to_client);
        }
        if (from_client != -1) {
            close(from_client);
        }
        unlink(WKP);
        exit(0);
    } else if (signo == SIGPIPE) {
        connected = 0;
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    while (1) {
        printf("Looking for client...\n");
        from_client = server_handshake( &to_client );
        printf("Client found!\n");
        connected = 1;
        while (connected) {
            int random = rand() % 101;
            write(to_client, &random, sizeof(int));
            sleep(1);
        }
        close(to_client);
        close(from_client);
    }
}
