typedef struct dataRecord {
    int Key;
} dataType;
    
typedef struct treeRecord {
    dataType Data;
    struct treeRecord* LChild;
    struct treeRecord* RChild;
} node;

typedef node* Nptr;

class BST {
    public:
    BST();
    BST(const BST& B);
    ~BST();

    Nptr Copy(Nptr T);
    void Destroy(Nptr T);
    
    Nptr Search(int Key);
    Nptr Search(Nptr T, int Key);

    Nptr Insert(int Key);
    Nptr Insert(Nptr T, int Key);

    void Delete(int Key);
    void Delete(Nptr T, int Key);
    void SuccessorCopy(Nptr& T, dataType& DelNodeData);

    void Print();
    void Print(Nptr T, int Lvl, bool R);

    private:
    Nptr Leaf;
};