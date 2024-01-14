#include "stackA.h"
#include <iostream>
using namespace std;

stackArray::stackArray() {
    Count = 0;
}

stackArray::stackArray(const stackArray& S) {
    this->Count = S.Count;
    for (int i = 0; i < S.Count; i++)
        this->Data[i] = S.Data[i];
}

stackArray::~stackArray() {}

void stackArray::AddLast(int Item) {
    if (Count == MAX)
        cout << "Array Full\n";
    else {
        Data[Count] = Item;
        Count++;
    }
}

void stackArray::RemoveLast() {
    if (Count == 0)
        cout << "Array Empty\n";
    else
        Count--;
}

void stackArray::RetrieveLast(int& Item) {
    Item = Data[Count - 1];
}

bool stackArray::IsEmpty() {
    return (Count == 0);
}

int stackArray::Length() {
    return Count;
}

void stackArray::Print() {
    cout << "Count : " << Count << '\n';
    for (int i = 0; i < Count; i++)
        cout << "Pos." << i << " : " << Data[i] << '\n';
    cout << '\n';
}