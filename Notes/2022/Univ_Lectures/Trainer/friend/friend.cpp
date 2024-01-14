#include <iostream>
using namespace std;

class Box;
class Container;
void print_all(Box b, Container c);

class Box {
    int box_count;
public:
    Box(int count) { this->box_count = count; }
    int get_count() { return this->box_count; }
    void print_count() { cout << "Box count : " << this->box_count << endl; }
    friend void print_all(Box b, Container c);
};

class Container {
    int cont_count;
public:
    Container(int count) { this->cont_count = count; }
    int get_count() { return this->cont_count; }
    void print_count() { cout << "Cont count : " << this->cont_count << endl; }
    friend void print_all(Box b, Container c);
};

void print_all(Box b, Container c) {
    cout << "Both count : " << b.box_count + c.cont_count << endl;
    // cout << "Both count : " << b.get_count + c.get_count << endl;
}

int main() {
    Box b(10);
    Container c(20);

    b.print_count();
    c.print_count();
    print_all(b, c);
}
