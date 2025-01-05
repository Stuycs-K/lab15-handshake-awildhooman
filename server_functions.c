#include "server_functions.h"

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