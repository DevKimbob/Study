#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void Init(listType *Lptr) {
    Lptr->Count = 0;
    Lptr->Head = NULL;
}

void Deconst(listType *Lptr) {
    Nptr front, back;
    front = Lptr->Head;

    while (front != NULL) {
        back = front;
        front = front->Next;
        free(back);
    }
}

void Insert(listType *Lptr, int Position, struct timer Item) {
    if ((Position > Lptr->Count) || (Position < 0)) 
        printf("Position out of range\n");
    else {
        Nptr p = (node *)malloc(sizeof(node));
        p->Timer = Item;

        if (Position == 0) {
            p->Next = Lptr->Head;
            Lptr->Head = p;
        }
        else {
            Nptr Temp = Lptr->Head;
            for (int i = 0; i < Position - 1; i++)
                Temp = Temp->Next;
            p->Next = Temp->Next;
            Temp->Next = p;
        }
        Lptr->Count += 1;
    }
}

void Delete(listType *Lptr, int Position, struct timer *ItemPtr) {
    Nptr p, Temp;

    if (Length(Lptr) == 0)
        printf("Deletion on empty list\n");
    else if ((Position > Lptr->Count) || (Position < 0))
        printf("Position out of range\n");
    else {
        if (Position == 0) {
            p = Lptr->Head;
            Lptr->Head = Lptr->Head->Next;
        }
        else {
            Temp = Lptr->Head;
            for (int i = 0; i < Position - 1; i++)
                Temp = Temp->Next;
            p = Temp->Next;
            Temp->Next = p->Next;
        }
        Lptr->Count -= 1;

        if (ItemPtr != NULL)
            *ItemPtr = p->Timer;
        free(p);
    }
}

void Retrieve(listType *Lptr, int Position, struct timer *ItemPtr) {
    if ((Position > Lptr->Count) || (Position < 0))
        printf("Position out of range\n");
    else {
        if (Position == 0) {
            *ItemPtr = Lptr->Head->Timer;
        }
        else {
            Nptr Temp = Lptr->Head;
            for (int i = 0; i < Position; i++)
                Temp = Temp->Next;
            *ItemPtr = Temp->Timer;
        }
    }
}

void Update(listType *Lptr, int Position, struct timer Item) {
    if ((Position > Lptr->Count) || (Position < 0))
        printf("Position out of range\n");
    else {
        if (Position == 0) {
            Lptr->Head->Timer = Item;
        }
        else {
            Nptr Temp = Lptr->Head;
            for (int i = 0; i < Position; i++)
                Temp = Temp->Next;
            Temp->Timer = Item;
        }
    }
}

void Update_i(listType *Lptr, int Position, int timechange) {
    if ((Position > Lptr->Count) || (Position < 0))
        printf("Position out of range\n");
    else {
        if (Position == 0) {
            Lptr->Head->Timer.Time += timechange;
        }
        else {
            Nptr Temp = Lptr->Head;
            for (int i = 0; i < Position; i++)
                Temp = Temp->Next;
            Temp->Timer.Time += timechange;
        }
    }
}

int FindPid(listType *Lptr, int Pid) {
    int pos = 0;
    Nptr Temp = Lptr->Head;

    while (Temp != NULL) {
        if (Temp->Timer.Pid == Pid) {
            return pos;
        }
        Temp = Temp->Next;
        pos++;
    }
    
    return -1;
}

void PrintList(listType *Lptr) {
    Nptr Temp = Lptr->Head;

    while (Temp != NULL) {
        printf("Time : %3d, Pid : %5d\n", Temp->Timer.Time, Temp->Timer.Pid);
        Temp = Temp->Next;
    }
}

int Length(listType *Lptr) {
    return Lptr->Count;
}