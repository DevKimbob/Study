typedef struct nodeRecord {
    int Data;
    struct nodeRecord* Next;
} node;
typedef node* Nptr;

class listList {
   public:
    listList();
    listList(const listList& L);
    ~listList();

    void Insert(int Position, int Item);
    void Delete(int Position);
    void Retrieve(int Position, int& Item);
    bool IsEmpty();
    int Length();
    void Print();

   private:
    int Count;
    Nptr Head;
};
