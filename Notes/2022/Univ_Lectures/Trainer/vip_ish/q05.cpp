#include <iostream>
using namespace std;

class Student {
    string name;
public:
    Student(string name = "") : name(name) {}
    string getName() { return name; }
    void setName(string name) { this->name = name; }
};

class MyClass {
    string className;
    Student *p;
    int size;
public:
    MyClass(int size) {
        string temp;
        this->size = size;
        p = new Student[size];
        for (int i = 0; i < size; i++) {
            cin >> temp;
            p[i].setName(temp);
        }
    }
    ~MyClass() {
        delete [] p;
    }
    void Print() {
        for (int i = 0; i < size; i++) {
            cout << p[i].getName() << " ";
        }
        cout << endl;
    }
};

int main() {
    MyClass mc(3);
    mc.Print();
}