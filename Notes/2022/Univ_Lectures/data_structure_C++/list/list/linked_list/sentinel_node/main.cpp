#include <iostream>

#include "listLS.h"
using namespace std;

int main() {
    listList a;
    a.Print();
    a.Insert(0, 10);
    a.Print();
    a.Insert(0, 0);
    a.Print();
    a.Insert(2, 20);
    a.Print();
    a.Delete(1);
    cout << "A\n";
    a.Print();
    // a.Delete(1);
    // a.Print();

    listList b(a);
    cout << "B\n";
    b.Print();
}