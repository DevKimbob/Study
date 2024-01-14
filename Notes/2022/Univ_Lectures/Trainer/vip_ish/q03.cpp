#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Circle {
private:
    int radius;
public:
    Circle();
    Circle(int radius);
    void setRadius(int radius);
    double getArea();
};


Circle::Circle() {
    this->radius = 1;
}

Circle::Circle(int radius) {
    this->radius = radius;
}

void Circle::setRadius(int radius) {
    this->radius = radius;
}

double Circle::getArea() {
    return 3.14 * radius * radius;
}

int main() {
    int size;
    int count = 0;
    cout << "Size : ";
    cin >> size;

    srand((unsigned int)time(NULL));

    Circle *arr_cir = new Circle [size];

    for (int i = 0; i < size; i++)
        arr_cir[i].setRadius(rand() % 100 + 1);

    for (int i = 0; i < size; i++) {
        if (arr_cir[i].getArea() > 100) {
            count++;
            cout << arr_cir[i].getArea() << " ";
        }
    }
    cout << endl << count << endl;

    delete [] arr_cir;
}