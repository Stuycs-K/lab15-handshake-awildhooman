#include "pipe_networking.h"
#include "server_functions.h"

int to_client = -1;
int from_client = -1;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (to_client != -1) {
            close(to_client);
        }
        if (from_client != -1) {
            close(from_client);
        }
        unlink(WKP);
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);
    while (1) {
        printf("Looking for client...\n");
        from_client = server_handshake( &to_client );
        while (1) {
            int random = rand() % 101;
            write(to_client, &random, sizeof(int));
            sleep(1);
        }
    }
}
