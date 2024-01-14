#include "bisrchTree.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Nptr BST::Insert(int Key) {
    if (Leaf == NULL) {
        Nptr p = new node;
        p->Data.Key = Key;
        p->LChild = NULL;
        p->RChild = NULL;
        Leaf = p;
        return p;
    }
    else
        return Insert(Leaf, Key);
}

Nptr BST::Insert(Nptr T, int Key) {
    if (T->Data.Key == Key) {
        cout << "Already in the tree\n";
        return T;
    }
    else if (T->Data.Key > Key) {
        if (T->LChild == NULL) {
            Nptr p = new node;
            p->Data.Key = Key;
            p->LChild = NULL;
            p->RChild = NULL;
            T->LChild = p;
            return p;
        }
        else
            return Insert(T->LChild, Key);
    }
    else {
        if (T->RChild == NULL) {
            Nptr p = new node;
            p->Data.Key = Key;
            p->LChild = NULL;
            p->RChild = NULL;
            T->RChild = p;
            return p;
        }
        else
            return Insert(T->RChild, Key);
    }
}