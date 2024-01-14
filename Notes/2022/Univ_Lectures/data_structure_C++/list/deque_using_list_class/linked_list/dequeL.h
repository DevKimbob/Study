#include "listL.h"

class dequeList {
    public:
    dequeList();
    dequeList(const dequeList& D);
    ~dequeList();

    void InsertFirst(int Item);
    void InsertLast(int Item);
    void DeleteFirst();
    void DeleteLast();
    void Retrieve(int Position, int& Item);
    bool IsEmpty();
    int Length();
    void Print();

    private:
    listList L;
};