#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utmp.h>

int main(int argc, char *argv[]) {
    struct utmp *ut;

    while ((ut = getutent()) != NULL) {
        printf("%s\n", ut->ut_user);  // oci...?
        
    }
}