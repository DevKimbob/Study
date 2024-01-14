#include "listLS.h"

#include <iostream>
using namespace std;

listList::listList() {
    Count = 0;
    Head = &Sentinel;
    Head->Data = 0;
    Head->Next = NULL;
}

listList::listList(const listList& L) {
    this->Count = L.Count;

    this->Head = &Sentinel;
    this->Head->Data = 0;
    this->Head->Next = NULL;

    Nptr temp1 = this->Head;
    Nptr temp2 = L.Head->Next;
    for (int i = 0; i < Count; i++) {
        Nptr p = new node;
        p->Data = temp2->Data;

        temp1->Next = p;
        p->Next = NULL;

        temp1 = temp1->Next;
        temp2 = temp2->Next;
    }
}

listList::~listList() {
    Nptr tmpF, tmpB;
    tmpF = Head->Next;

    while (tmpF != NULL) {
        tmpB = tmpF;
        tmpF = tmpF->Next;
        delete tmpB;
    }
}

void listList::Insert(int Position, int Item) {
    if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else {
        Nptr temp = Head;
        Nptr p = new node;
        p->Data = Item;

        for (int i = 0; i < Position; i++) 
           temp = temp->Next; 
        
        p->Next = temp->Next;
        temp->Next = p;

        Count++;
    }
}

void listList::Delete(int Position) {
    if (Count == 0)
        cout << "List Empty\n";
    else if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else {
        Nptr temp = Head;
        Nptr p = new node;
        for (int i = 0; i < Position; i++)
            temp = temp->Next;

        p = temp->Next;
        temp->Next = p->Next;
        delete p;

        Count--; 
    }
}

void listList::Retrieve(int Position, int& Item) {
    Nptr temp;

    for (int i = 0; i < Position; i++)
        temp = temp->Next;

    Item = temp->Data;
}

bool listList::IsEmpty() {
    return (Count == 0);
}

int listList::Length() {
    return Count;
}

void listList::Print() {
    cout << "Count : " << Count << '\n';
    Nptr temp = Head;
    for (int i = 0; i < Count; i++) {
        temp = temp->Next;
        cout << "Pos." << i << " : " << temp->Data << '\n';
    }
    cout << '\n';
}
