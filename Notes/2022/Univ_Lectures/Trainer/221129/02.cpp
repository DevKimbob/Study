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
	void print() {cout << "hello" << endl;}
	int getx() { return x; }
	int gety() { return y; }
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
};

int main() {
    ThreeDPoint tdp1(1, 2, 3);

	tdp1.print();
}