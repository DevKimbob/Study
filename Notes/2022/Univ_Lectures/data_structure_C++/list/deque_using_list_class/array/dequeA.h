#include "listA.h"

class dequeArray {
    public:
    dequeArray();
    dequeArray(const dequeArray& D);
    ~dequeArray();

    void InsertFirst(int Item);
    void InsertLast(int Item);
    void DeleteFirst();
    void DeleteLast();
    void Retrieve(int Position, int& Item);
    bool IsEmpty();
    int Length();
    void Print();

    private:
    listArray L;
};