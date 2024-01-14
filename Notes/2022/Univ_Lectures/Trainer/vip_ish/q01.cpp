#include <iostream>
using namespace std;

int main() {
    int cnt;

    cout << "Count : ";
    cin >> cnt;

    int *int_arr = new int [cnt];

    for (int i = 0; i < cnt; i++) {
        cout << "Enter : ";
        cin >> int_arr[i];
    }

    for (int i = 0; i < cnt; i++)
        cout << int_arr[i] << " ";
    cout << endl;
    
    delete [] int_arr;
}