#include <stdio.h>

#include "list.h"

int main() {
    listType list;
    listType *lptr = &list;

    Init(lptr);
    Insert(lptr, 10, "tset1");
    Insert(lptr, 20, "tset2");
    Print(lptr);
    Change(lptr, 20, "tset4");
    Print(lptr);
}