#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

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
        printf(" # No such PID : %d\n", Pid);
    }
    else {
        printf("  (Removing PID : %d)\n", front->Data);
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
        printf(" # No such PID : %d\n", Pid);
    }
    else {
        printf("  (Changing PID_%d's Login_id)\n", front->Data);
        for (i = 0; i < 32; i++) {
            front->Name[i] = 0;
        }
        max = (strlen(Id) < 32) ? strlen(Id) : 32;
        for (i = 0; i < max; i++)
            front->Name[i] = Id[i];
    }
}

int Find(listType *Lptr, int Pid) {
    Nptr front = Lptr->Head, back = NULL;

    while ((front != NULL) && (front->Data != Pid)) {
        back = front;
        front = front->Next;
    }

    if (front == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

int Length(listType* Lptr) {
    return Lptr->Count;
}

void Print(listType* Lptr) {
    Nptr front = Lptr->Head->Next;

    while (front != NULL) {
        printf("  %6d : ", front->Data);
        if (strcmp("0", front->Name) == 0) {
            printf("-- not logged in --\n");
        }
        else {
            printf("%s\n", front->Name);
        }
        front = front->Next;
    }
}
