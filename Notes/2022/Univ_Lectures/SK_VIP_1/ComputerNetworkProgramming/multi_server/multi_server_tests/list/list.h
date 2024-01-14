#ifndef __LIST_H__
#define __LIST_H__

typedef struct node {
    int Data;
    char Name[32];
    struct node *Next;
} node;
typedef node *Nptr;

typedef struct {
    int Count;
    node Sentinel;
    Nptr Head;
} listType;

void Init(listType *Lptr);
void Insert(listType *Lptr, int Pid, char *Id);
void Delete(listType *Lptr, int Pid);
void DeleteAll(listType *Lptr);
int DeleteFirst(listType *Lptr);
void Change(listType *Lptr, int Pid, char *Id);
int Length(listType *Lptr);
void Print(listType *Lptr);

#endif