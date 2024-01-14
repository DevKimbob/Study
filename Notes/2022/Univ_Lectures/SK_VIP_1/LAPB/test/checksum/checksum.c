#include <stdio.h>
#include <sys/types.h>

#include "checksum.h"

void print_binary(int n, int len) {
    int pwr_two = 1;
    int count = 0;

    while (n >= pwr_two) {
        pwr_two *= 2;
        count++;
    }
    if (count) {
        pwr_two /= 2;
        // count--;
    }

    // printf("n : %d, pwr_two : %d, count : %d\n", n, pwr_two, count);

    for (int i = 0; i < len - count; i++) {
        printf("0");
    }

    while (count) {
        if (n >= pwr_two) {
            printf("1");
            n -= pwr_two;
        }
        else {
            printf("0");
        }
        pwr_two /= 2;
        count--;
    }
    puts("");
}

int make_checksum(int *arr_int, int size, int len) {
    int checksum = 0;
    int mask = 1;

    for (int i = 0; i < len; i++) {
        mask *= 2;
    }
    mask--;

    for (int i = 0; i < size; i++) {
        checksum += arr_int[i];
    }

    // printf("checksum : %d\n", checksum);
    // printf("mask : %d\n", mask);
    while (checksum > mask) {
        // printf("c&m : %d, c>>l : %d\n", checksum & mask, checksum >> len);
        checksum = (checksum & mask) + (checksum >> len);
        // printf("checksum : %d\n\n", checksum);
    }

    print_binary(checksum, len);
    printf("final checksum : %d\n", checksum);

    return checksum;
}

int make_checksum_i(int target, int len) {
    int checksum = 0;
    int mask = 1;

    for (int i = 0; i < len; i++) {
        mask *= 2;
    }
    mask--;

    checksum = target;

    while (checksum > mask) {
        checksum = (checksum & mask) + (checksum >> len);
    }

    print_binary(checksum, len);
    printf("final checksum : %d\n", checksum);

    return checksum;
}

int main() {
    // for (int i = 0; i < size; i++) {

    // }
    // int arr_int[2] = {10, 20};
    int arr_int[2] = {20, 30};

    for (int i = 0; i < 2; i++) 
        print_binary(arr_int[i], LEN);

    make_checksum(arr_int, 2, LEN);

    make_checksum_i(14, 3);
    // print_binary(make_checksum(arr_int, 2, LEN), LEN);

    // u_char a = 10;
    // u_char b = 255 - a;

    // printf("a : %d, b : %d\n", a, b);
    // print_binary(a, 8);
    // print_binary(b, 8);

    // u_char c = 250;
    // u_char d = c + 10;
    // printf("c : %d, d : %d\n", c, d);
    // print_binary(c, 8);
    // print_binary(d, 8);
}