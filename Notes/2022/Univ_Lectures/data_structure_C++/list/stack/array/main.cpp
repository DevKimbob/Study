#include "stackA.h"
#include <iostream>
using namespace std;

int main() {
    stackArray a;
    a.AddLast(10);
    a.Print();
    a.AddLast(20);
    a.Print();
    a.AddLast(30);
    a.Print();
    a.RemoveLast();
    a.Print();
}