const int MAX = 100;

class stackArray {
    public:
    stackArray();
    stackArray(const stackArray& S);
    ~stackArray();

    void AddLast(int Item);
    void RemoveLast();
    void RetrieveLast(int& Item);
    bool IsEmpty();
    int Length();
    void Print();

    private:
    int Count;
    int Data[MAX];
};