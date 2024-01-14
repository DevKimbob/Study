#include <iostream>
using namespace std;

class Time {
public:
    int hour, min, sec;
    Time() {
        this->hour = 0; this->min = 0; this->sec = 0;
    }
    Time(int h, int m, int s) {
        this->hour = h, this->min = m, this->sec = s;
    }
    void Print() {
        cout << hour << " : " << min << " : " << sec << endl;
    }
};

bool Equal(Time& t1, Time& t2) {
    if ((t1.hour == t2.hour) && (t1.min == t2.min) && (t1.sec == t2.sec))
        return true;
    return false;
}

bool Equal(Time *t1, Time*t2) {
    if ((t1->hour == t2->hour) && (t1->min == t2->min) && (t1->sec == t2->sec))
        return true;
    return false;
}

int main() {
    Time t1(1, 2, 3);
    Time t2(1, 2, 3);
    Time t3(1, 2, 5);

    if (Equal(t1, t2))
        cout << "T" << endl;
    else
        cout << "F" << endl;
    
    if (Equal(&t1, &t3))
        cout << "T" << endl;
    else
        cout << "F" << endl;
}