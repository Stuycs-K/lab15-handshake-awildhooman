#include "pipe_networking.h"

int to_server = -1;
int from_server = -1;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        if (to_server != -1) {
            close(to_server);
        }
        if (from_server != -1) {
            close(from_server);
        }
        exit(0);
    }
}

int main() {
    signal(SIGINT, sighandler);

    from_server = client_handshake( &to_server );
    char lineBuffer[100];
    fgets(lineBuffer, sizeof(lineBuffer), stdin);
    write(to_server, lineBuffer, sizeof(lineBuffer));
    read(from_server, lineBuffer, sizeof(lineBuffer));
    printf("%s", lineBuffer);
}
