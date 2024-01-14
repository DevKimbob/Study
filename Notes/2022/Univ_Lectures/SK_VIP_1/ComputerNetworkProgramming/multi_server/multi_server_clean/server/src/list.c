#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

void Init(listType* Lptr) {
    Lptr->Count = 0;
    Lptr->Head = &Lptr->Sentinel;
    Lptr->Head->Data = -1;
    Lptr->Head->Name[0] = '\0';
    Lptr->Head->Next = NULL;
}

void Insert(listType* Lptr, int Pid, char Id[32]) {
    int i;

    Nptr p = (node*)malloc(sizeof(node));
    p->Data = Pid;
    p->Next = Lptr->Head->Next;
    for (i = 0; i < 32; i++)
        p->Name[i] = Id[i]; 

    Lptr->Head->Next = p;
    Lptr->Count += 1;
}

void Delete(listType* Lptr, int Pid) {
    Nptr front = Lptr->Head, back = NULL;

    while ((front != NULL) && (front->Data != Pid)) {
        back = front;
        front = front->Next;
    }

    if (front == NULL) {
        printf("No such PID : %d\n", Pid);
    }
    else {
        printf("Removing PID : %d\n", front->Data);
        back->Next = front->Next;
        free(front);
        Lptr->Count -= 1;
    }
}

void DeleteAll(listType* Lptr) {
    Nptr front = Lptr->Head->Next, back = NULL;

    while (front != NULL) {
        back = front;
        front = front->Next;

        free(back);
    }

    Lptr->Head->Next = NULL;
    Lptr->Count = 0;
}

int DeleteFirst(listType* Lptr) {
    int pid;

    Nptr front = Lptr->Head->Next, back = NULL;

    if (front != NULL) {
        pid = front->Data;
        back = front;
        front = front->Next;

        free(back);
    }

    Lptr->Head->Next = front;
    Lptr->Count -= 1;

    return pid;
}

int Length(listType* Lptr) {
    return Lptr->Count;
}

void Print(listType* Lptr) {
    Nptr front = Lptr->Head->Next;

    while (front != NULL) {
        printf("%d : %s\n", front->Data, front->Name);
        front = front->Next;
    }
}