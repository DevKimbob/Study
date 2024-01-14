#include <stdio.h>

#include "header.h"

int c = 3;

extern int b;

void set_a_to_0() {
    a = 0;
}

void a_add_1() {
    a += 1;
}

void print_a() {
    printf("a : %d\n", a);
}

void print_b() {
    printf("b : %d\n", b);
}

void print_d() {
    printf("d : %d\n", d);
}