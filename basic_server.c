#include "pipe_networking.h"

void modify(char *str, int rotate) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = (*str - 'A' + rotate) % 26 + 'A';
        } else if (*str >= 'a' && *str <= 'z') {
            *str = (*str - 'a' + rotate) % 26 + 'a';
        }
        str++;
    }
}

int main() {
    int to_client;
    int from_client;
    srand(time(NULL));
    while (1) {//getting new clients
        from_client = server_handshake( &to_client );
        char lineBuffer[100];
        read(from_client, lineBuffer, sizeof(lineBuffer));
        modify(lineBuffer, rand());
        write(to_client, lineBuffer, sizeof(lineBuffer));
    }
}
