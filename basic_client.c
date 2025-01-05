#include "pipe_networking.h"

int main() {
    int to_server;
    int from_server;

    from_server = client_handshake( &to_server );
    char lineBuffer[100];
    fgets(lineBuffer, sizeof(lineBuffer), stdin);
}
