#include "listL.h"

#include <iostream>
using namespace std;

listList::listList() {
    Count = 0;
    Head = NULL;
}

listList::listList(const listList& L) {
    this->Count = L.Count;
    Nptr temp2 = L.Head;

    if (L.Count != 0) {
        Nptr p = new node;
        p->Data = temp2->Data;
        this->Head = p;
        Nptr temp1 = p; 

        for (int i = 0; i < L.Count - 1; i++) {
            Nptr p = new node;
            temp2 = temp2->Next;

            p->Data = temp2->Data;
            temp1->Next = p;
            p->Next = NULL;

            temp1 = temp1->Next;
        }
    }
}

listList::~listList() {
    Nptr tmpF, tmpB;
    tmpF = Head;

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
        for (int i = 0; i < Position - 1; i++)
            temp = temp->Next;

        Nptr p = new node;
        p->Data = Item;
		if (Position == 0) {
			p->Next = Head;
			Head = p;
		}
		else {
			p->Next = temp->Next;
			temp->Next = p;
		}

        Count++;
    }
}

void listList::Delete(int Position) {
    if (Count == 0)
        cout << "List Empty\n";
    else if ((Position < 0) || (Position > Count))
        cout << "Wrong Position\n";
    else {
        Nptr p, temp;
        temp = Head;

        for (int i = 0; i < Position - 1; i++)
            temp = temp->Next;

        p = temp->Next;
        temp->Next = temp->Next->Next;

        delete p;
        
        Count--;
    }
}

void listList::Retrieve(int Position, int& Item) {
    Nptr temp = Head;

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
        cout << "Pos." << i << " : " << temp->Data << '\n';
        temp = temp->Next;
    }
    cout << '\n';
}
