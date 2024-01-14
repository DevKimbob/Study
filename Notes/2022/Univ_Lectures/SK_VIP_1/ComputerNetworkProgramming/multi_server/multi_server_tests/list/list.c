#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void Init(listType* Lptr) {
    Lptr->Count = 0;
    Lptr->Head = &Lptr->Sentinel;
    Lptr->Head->Data = -1;
    Lptr->Head->Name[0] = '0';
    Lptr->Head->Next = NULL;
}

void Insert(listType* Lptr, int Pid, char *Id) {
    int i, max;

    Nptr p = (node*)malloc(sizeof(node));
    p->Data = Pid;
    p->Next = Lptr->Head->Next;
    max = (strlen(Id) < 32) ? strlen(Id) : 32;
    for (i = 0; i < max; i++)
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

void Change(listType *Lptr, int Pid, char *Id) {
    int i, max;

    Nptr front = Lptr->Head, back = NULL;

    while ((front != NULL) && (front->Data != Pid)) {
        back = front;
        front = front->Next;
    }

    if (front == NULL) {
        printf("No such PID : %d\n", Pid);
    }
    else {
        printf("Changing PID's Login_id : %d\n", front->Data);
        max = (strlen(Id) < 32) ? strlen(Id) : 32;
        for (i = 0; i < max; i++)
            front->Name[i] = Id[i];
    }
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