#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int cost;
    int index;
} node;

typedef struct heap {
    int arrlen;
    int datalen;
    node *nptr;
} heap;

void init(heap *h);
void deconst(heap *h);

void push(heap *h, node n);
node pop(heap *h);

void print(heap *h);

#endif