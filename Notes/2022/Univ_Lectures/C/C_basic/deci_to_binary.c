#include <stdio.h>

int main() {
    unsigned int num;
    printf("Decimal : ");
    scanf("%d", &num);

    int len = 0;
    unsigned int two_power_len = 1;
    while(two_power_len < num) {
        two_power_len *= 2;
        len++;
    }
    unsigned int mask = (len) ? (1 << (len - 1)) : 1;
    
    printf("Binary : ");
    while(mask) {
        (num & mask) ? printf("1") : printf("0");
        mask = mask >> 1;
    }

    printf("\n");
    return 0;
}