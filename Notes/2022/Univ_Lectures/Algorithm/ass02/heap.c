#include "heap.h"

void init(heap *h) {
    h->arrlen = 1;
    h->datalen = 0;
    h->nptr = (node *)malloc(sizeof(node));
}

void deconst(heap *h) {
    free(h->nptr);
}

void push(heap *h, node n) {
    int index;

    if (h->datalen + 1 == h->arrlen)
        h->nptr = realloc(h->nptr, h->arrlen + 1);

    h->arrlen += 1;
    h->datalen += 1;

    //sort
    index = h->datalen;
    while ((index != 1) && (n.cost < h->nptr[index / 2].cost)) {
        h->nptr[index] = h->nptr[index / 2];
        index /= 2;
    }
    h->nptr[index] = n;
}

node pop(heap *h) {
    int pindex, cindex;
    int index;
    node out;
    node *Nptr = h->nptr;

    out = Nptr[1];

    //sort
    cindex = 2;
    while (cindex <= h->datalen - 1) {
        if ((cindex < h->datalen - 1) && (Nptr[cindex].cost > Nptr[cindex + 1].cost))
            cindex++;

        if (Nptr[h->datalen].cost < Nptr[cindex].cost)
            break;

        Nptr[cindex / 2] = Nptr[cindex];

        cindex *= 2;
    }
    Nptr[cindex / 2] = Nptr[h->datalen];
    h->datalen -= 1;

    return out;
}

void print(heap *h) {
    printf("arrlen : %d\n", h->arrlen);
    printf("datalen : %d\n", h->datalen);

    for (int i = 1; i < h->datalen + 1; i++) {
        printf("%2d Cost : %d\n", i, h->nptr[i].cost);
        printf("%2d Index : %d\n", i, h->nptr[i].index);
    }
}