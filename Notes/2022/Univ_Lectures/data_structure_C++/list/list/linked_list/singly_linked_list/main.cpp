#include <iostream>

#include "listL.h"
using namespace std;

int main() {
    listList a;
    a.Print();
    a.Insert(0, 10);
    a.Print();
    a.Insert(0, 0);
    a.Print();
    a.Insert(2, 20);

    cout << "A\n";
    a.Print();
    
    listList b = a;
    cout << "B\n";
    b.Print();

    a.Delete(1);
    cout << "A.2\n";
    a.Print();

    cout << "B.2\n";
    b.Print();
    
    int Item;
    b.Retrieve(1, Item);
    cout << Item << '\n';
}