#include <stdio.h>

void fun(int a) {
    printf("a : %d\n", a);
}

void add(int a, int b) {
    printf("a + b = %d\n", a + b);
}

void sub(int a, int b) {
    printf("a - b = %d\n", a - b);
}

int main() {
    void (*fun_ptr)(int) = &fun;
    (*fun_ptr)(10);

    void (*fun_ptr2)(int) = fun;
    fun_ptr2(20);

    void (*fun_ptr_arr[])(int, int) = {add, sub};
    int a = 30, b = 40;

    for (int i = 0; i < 2; i++) {
        fun_ptr_arr[i](a, b);
    }
}