#include "pipe_networking.h"
#include "server_functions.h"

int main() {
    int to_client;
    int from_client;
    srand(time(NULL));
    from_client = server_handshake( &to_client );
    char lineBuffer[100];
    read(from_client, lineBuffer, sizeof(lineBuffer));
    modify(lineBuffer, rand());
    write(to_client, lineBuffer, sizeof(lineBuffer));
}
