#include "dequeA.h"
#include <iostream>
using namespace std;

dequeArray::dequeArray() {}

dequeArray::dequeArray(const dequeArray& D) {
    L = D.L;
    // for (int i = 0; i < D.L.Length(); i++) {
    //     int temp;
    //     L.Retrieve(i, temp);
    //     L.Insert(i, temp);
    // }
}

dequeArray::~dequeArray() {}

void dequeArray::InsertFirst(int Item) {
    L.Insert(0, Item);
}

void dequeArray::InsertLast(int Item) {
    L.Insert(L.Length(), Item);
}

void dequeArray::DeleteFirst() {
    L.Delete(0);
}

void dequeArray::DeleteLast() {
    L.Delete(L.Length() - 1);
}

void dequeArray::Retrieve(int Position, int& Item) {
    L.Retrieve(Position, Item);
}

bool dequeArray::IsEmpty() {
    return L.IsEmpty();
}

int dequeArray::Length() {
    return L.Length();
}

void dequeArray::Print() {
    L.Print();
}