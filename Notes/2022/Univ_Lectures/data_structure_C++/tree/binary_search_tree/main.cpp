#include "biSrchTree.h"
#include <iostream>
using namespace std;

int main() {
    BST a;
    Nptr temp = NULL;

    a.Insert(20);
    a.Insert(60);
    a.Insert(10);
    a.Insert(0);
    a.Insert(40);
    a.Insert(30);
    a.Insert(70);
    a.Insert(50);

    // cout << "A\n";
    a.Print();

    // cout << a.Leaf->RChild->RChild->Data.Key << endl;
    // cout << a.Leaf->RChild->LChild->RChild->Data.Key << endl;
    a.Delete(60);
    a.Print();

    a.Delete(20);
    a.Print();

    temp = a.Search(40);
    cout.width(3);
    cout << temp->RChild->Data.Key << endl;

    BST b = a;
    b.Print();
}