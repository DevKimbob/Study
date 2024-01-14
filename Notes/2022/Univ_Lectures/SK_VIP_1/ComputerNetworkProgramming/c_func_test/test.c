#include <stdio.h>

int test_func();

int main(argc, argv)
int argc;
char *argv[];
{
    int in1 = 10, in2 = 20;
    int size;

    printf("argc : %d\n", argc);
    test_func(in1, &in2);
    printf("after test_func in2 : %d\n", in2);

    size = sizeof in1;
    printf("size : %d\n", size);
}

int test_func(in1, in2)
int in1, *in2;
{
    printf("in1 : %d\n", in1);
    printf("in2++ : %d\n", (*in2)++);
}