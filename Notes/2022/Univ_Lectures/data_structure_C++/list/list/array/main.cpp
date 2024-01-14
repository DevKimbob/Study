#include <iostream>

#include "listA.h"
using namespace std;

int main() {
    listArray a;
    a.Insert(0, 10);
    a.Insert(0, 0);
    a.Insert(2, 20);
    a.Print();

    a.Delete(1);
    a.Print();

    int b;
    a.Retrieve(1, b);
    cout << b << endl;
}