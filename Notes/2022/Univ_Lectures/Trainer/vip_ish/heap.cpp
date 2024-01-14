#include <iostream>
using namespace std;

class Circle {
    int radius;
    public:
    Circle();
    Circle(int r);
    ~Circle();
    void setRadius(int r) { radius = r; }
    double getArea() { return 3.14 * radius * radius; }
};

Circle::Circle() {
    radius = 1;
    cout << "const r : " << radius << endl;
}

Circle::Circle(int r) {
    radius = r;
    cout << "const r : " << radius << endl;
}

Circle::~Circle() {
    cout << "deconst" << endl;
}

int main() {
    Circle *p, *q;
    Circle r;

    p = new Circle();
    q = new Circle(30);


    cout << p->getArea() << endl << q->getArea() << endl;

    delete p;
    delete q;
}