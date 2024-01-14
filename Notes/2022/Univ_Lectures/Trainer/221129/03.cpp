#include <iostream>
using namespace std;
class Box {
private:
	int length;
	int width;
	int heigth;
public:
	Box(int l = 0, int w = 0, int h = 0) : length{ l }, width{ w }, heigth{ h }{}

	double getVolume(void) {
		return length * width * heigth;
	}
	void print() {
		cout << "상자의 길이 : " << length << endl;
		cout << "상자의 너비 : " << width << endl;
		cout << "상자의 높이 : " << heigth << endl;
		cout << "상자의 부피 : " << getVolume() << endl<<endl;
	
	}
	Box operator+(const Box& v2) {
		Box v;
		v.length = this->length + v2.length;
		v.width = this->width + v2.width;
		v.heigth = this->heigth + v2.heigth;	
		return v;
	}
};
int main() {
	Box a(10, 10, 10);

	Box b(20, 20, 20);
	
	Box c;
	c = a + b;

    a.print();
    b.print();
    c.print();

	return 0;
}