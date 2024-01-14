#include <stdio.h>
#include <stdlib.h>

int main() {
    int ret;
    ret = system("ps -ef | grep sshd > sshd.txt");
    printf("Return Value : %d\n", ret);
}