typedef struct nodeRecord {
    int Data;
    struct nodeRecord* Next;
} node;
typedef node* Nptr;

class stackList {
    public:
    stackList();
    stackList(const stackList& S);
    ~stackList();

    void AddLast(int Item);
    void RemoveLast();
    void RetrieveLast(int& Item);
    bool IsEmpty();
    int Length();
    void Print();

    private:
    int Count;
    Nptr Head; 
};