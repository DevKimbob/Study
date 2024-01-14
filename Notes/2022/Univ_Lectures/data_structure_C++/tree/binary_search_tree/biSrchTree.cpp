#include "biSrchTree.h"
#include <iostream>
using namespace std;

const char SPACE[] = "   ";

BST::BST() {
    Leaf = NULL;
}

BST::BST(const BST& B) {
    this->Leaf = Copy(B.Leaf);
}

BST::~BST() {
    Destroy(Leaf);
}

Nptr BST::Copy(Nptr T) {
    if (T == NULL)
        return NULL;
    else {
        Nptr p = new node;
        p->Data.Key = T->Data.Key;
        p->LChild = Copy(T->LChild);
        p->RChild = Copy(T->RChild);
        return p;
    }
}

void BST::Destroy(Nptr T) {
    if (T != NULL) {
        Destroy(T->LChild);
        Destroy(T->RChild);
        delete T;
    }
}

Nptr BST::Search(int Key) {
    return Search(Leaf, Key);
}

Nptr BST::Search(Nptr T, int Key) {
    if (T == NULL) {
        cout << "No such data\n";
        return NULL;
    }
    else if (T->Data.Key == Key)
        return T;
    else if (T->Data.Key > Key)
        return Search(T->LChild, Key);
    else
        return Search(T->RChild, Key);
}

Nptr BST::Insert(int Key) {
    Nptr T = Insert(Leaf, Key);
    if (Leaf == NULL)
        Leaf = T;
    return T;
}

Nptr BST::Insert(Nptr T, int Key) {
    if (T == NULL) {
        T = new node;
        T->Data.Key = Key;
        T->LChild = NULL;
        T->RChild = NULL;
    }
    else if (T->Data.Key == Key)
        cout << "Already in the tree\n";
    else if (T->Data.Key > Key)
        T->LChild = Insert(T->LChild, Key);
    else
        T->RChild = Insert(T->RChild, Key);
    
    return T;
}

void BST::Delete(int Key) {
    Delete(Leaf, Key);
}

void BST::Delete(Nptr T, int Key) {
    if (T == NULL)
        cout << "No such data\n";
    else if (T->Data.Key > Key)
        Delete(T->LChild, Key);
    else if (T->Data.Key < Key)
        Delete(T->RChild, Key);
    else {
        if ((T->LChild == NULL) && (T->RChild == NULL)) {
            Nptr temp = T;
            T = NULL;
            delete temp;
        }
        else if (T->LChild == NULL) {
            Nptr temp = T;
            T = T->LChild;
            delete temp;
        }
        else if (T->RChild == NULL) {
            Nptr temp = T;
            T = T->RChild;
            delete temp;
        }
        else {
            SuccessorCopy(T->RChild, T->Data);
        }
    }
}

void BST::SuccessorCopy(Nptr& T, dataType& DelNodeData) {
    if (T->LChild == NULL) {
        DelNodeData.Key = T->Data.Key;
        Nptr temp = T;
        T = T->RChild;
        delete temp;
    }
    else
        SuccessorCopy(T->LChild, DelNodeData);
}

void BST::Print() {
    Print(Leaf, 0, true);
}

void BST::Print(Nptr T, int Lvl, bool R) {
    if (T != NULL) {
        if (!R) {
            cout << '\n';
            for (int i = 0; i < Lvl; i++)
                cout << SPACE;
        }
        cout.width(3);
        cout << T->Data.Key;

        Print(T->RChild, Lvl + 1, true);
        Print(T->LChild, Lvl + 1, false);
    }
    
    if (Lvl == 0)
        cout << "\n\n";
}