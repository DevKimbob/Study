#include <iostream>
#include <string>

using namespace std;

class ThreeDPoint;

class Point {
	int x, y;
	friend class ThreeDPoint;
public:
	// friend class ThreeDPoint;
	Point(int a = 0, int b = 0) {
		x = a;
		y = b;
	}
	~Point() {}
	int getx() { return x; }
	int gety() { return y; }
	// Point operator+(Point p2) {
	// 	Point p;

	// 	p.x = this->x + p2.x;
	// 	p.y = this->y + p2.y;

	// 	return p;
	// }
};

class ThreeDPoint : public Point {
	int z;
public:
	ThreeDPoint(int a = 0 , int b = 0, int c = 0) : Point(a, b), z(c) {}
	~ThreeDPoint() {}
	void print() {
		// cout << "(" << getx() << ", " << gety() << ", " << z << ")" << endl;
		cout << "(" << x << ", " << y << ", " << z << ")" << endl;
	}
	// ThreeDPoint operator+(ThreeDPoint p2)
	// {
	// 	int a, b, c;

	// 	ThreeDPoint p;

	// 	// p.operator+(p2);

	// 	a = this->getx() + p2.getx();
	// 	b = this->gety() + p2.gety();
	// 	c = this->z + p2.z;
	// 	ThreeDPoint p(a, b, c);

	// 	return p;
	// };
};

int main() {
    ThreeDPoint tdp1(1, 2, 3);
	tdp1.print();
    // ThreeDPoint tdp2(6, 7, 8);
    // ThreeDPoint tdp3;

    // tdp3 = tdp1 + tdp2;

    // tdp3.print();

}