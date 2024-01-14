#include "dequeA.h"
#include <iostream>
using namespace std;

int main() {
    dequeArray a;
    a.InsertFirst(10);
    a.InsertFirst(0);
    a.InsertLast(20);
    cout << "A\n";
    a.Print();

    dequeArray b(a);
    cout << "B\n";
    b.Print();

    a.DeleteFirst();
    cout << "A.2\n";
    a.Print();
    
    cout << "B.2\n";
    b.Print();
}