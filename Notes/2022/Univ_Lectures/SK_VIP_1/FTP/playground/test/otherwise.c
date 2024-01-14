#include <stdio.h>

int main() {
    int i;
    int comp = 0;

    for (i = 0; i < 10; i++) {
        switch (i) {
            case 1:
                puts("i : 1");
                break;
            case 2:
                puts("i : 2");
                break;
            otherwise:
                printf("otherwise, i : %d\n", i);
        }
    }

    printf("After for, i : %d\n", i);

    label_1:
        puts("Inside label_1");
    
    i = 135;
    if (comp == 0) {
        comp = 1;
        puts("Before goto otherwise");
        goto otherwise;
    }

    return 0;
}