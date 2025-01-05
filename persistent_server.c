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
        exit(0);
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);
    while (1) {
        from_client = server_handshake( &to_client );
        char lineBuffer[100];
        read(from_client, lineBuffer, sizeof(lineBuffer));
        modify(lineBuffer, rand());
        write(to_client, lineBuffer, sizeof(lineBuffer));
        close(to_client);
        close(from_client);
    }
}
