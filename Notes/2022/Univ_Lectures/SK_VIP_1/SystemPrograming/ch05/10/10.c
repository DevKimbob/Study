#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    gid_t gid, egid;

    gid = getgid();
    egid = getegid();

    printf("GID = %d, EGID = %d\n", (int)gid, (int)egid);
}