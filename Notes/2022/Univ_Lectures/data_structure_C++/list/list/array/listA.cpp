#include "listA.h"

#include <iostream>
using namespace std;

listArray::listArray() {
    Count = 0;
}

listArray::listArray(const listArray& L) {
    this->Count = L.Count;
    for (int i = 0; i < this->Count; i++) {
        this->Data[i] = L.Data[i];
    }
}

listArray::~listArray() {}

void listArray::Insert(int Position, int Item) {
    if (Count == MAX)
        cout << "Array Full\n";
    else if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else {
        for (int i = 0; i < Count - Position; i++) {
            Data[Count - i] = Data[Count - i - 1];
        }
        Data[Position] = Item;
        Count++;
    }
}

void listArray::Delete(int Position) {
    if (Count == 0)
        cout << "Array Empty\n";
    else if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else {
        for (int i = 0; i < Count - Position; i++)
            Data[Position + i] = Data[Position + i + 1];
        Count--;
    }
}

void listArray::Retrieve(int Position, int& Item) {
    if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else
        Item = Data[Position];
}

bool listArray::IsEmpty() {
    return (Count == 0);
}

int listArray::Length() {
    return Count;
}

void listArray::Print() {
    cout << "Count : " << Count << '\n';
    for (int i = 0; i < Count; i++)
        cout << "Pos." << i << " : " << Data[i] << '\n';
    cout << '\n';
}