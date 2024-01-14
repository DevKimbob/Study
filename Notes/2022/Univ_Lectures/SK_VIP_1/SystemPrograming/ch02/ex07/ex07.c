#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (rmdir("han") == -1) {
        perror("han");
        exit(1);
    }
}