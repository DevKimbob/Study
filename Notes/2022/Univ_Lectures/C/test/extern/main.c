#include <stdio.h>

#include "header.h"

int b = 1;

extern int c;
extern int d;

extern void set_a_to_0();
extern void a_add_1();
extern void print_a();
extern void print_b();
extern void print_d();

int main() {
    printf("test\n");

    set_a_to_0();
    a_add_1();

    printf("a : %d\n", a);
    print_a();

    b++;

    print_b();
    printf("c : %d\n", c);

    printf("d : %d\n", d);
    print_d();
}