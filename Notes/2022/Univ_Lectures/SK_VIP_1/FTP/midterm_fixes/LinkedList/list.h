#ifndef _LIST_H_
#define _LIST_H_

typedef struct timer {
    int Time;
    int Pid;
} timer;

typedef struct node {
    struct timer Timer;
    struct node *Next;
} node;
typedef node *Nptr;

typedef struct {
    int Count;
    Nptr Head;
} listType;

void Init(listType *Lptr);
void Deconst(listType *Lptr);

void Insert(listType *Lptr, int Position, struct timer Item);
void Delete(listType *Lptr, int Position, struct timer *ItemPtr);
void Retrieve(listType *Lptr, int Position, struct timer *ItemPtr);
void Update(listType *Lptr, int Position, struct timer Item);
void Update_i(listType *Lptr, int Position, int timechange);
int FindPid(listType *Lptr, int Pid);

void PrintList(listType *Lptr);
int Length(listType *Lptr);

#endif