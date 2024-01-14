#include <iostream>
using namespace std;

int main() {
    int cnt;
    string temp;

    cout << "Count : ";
    cin >> cnt;
    cin.ignore(100, '\n');
    // getline(cin, temp, '\n');

    string *int_arr = new string [cnt];

    for (int i = 0; i < cnt; i++) {
        cout << "Enter : ";
        getline(cin, temp, '\n');
        int_arr[i] = temp;
        // cin >> int_arr[i];
    }

    for (int i = 0; i < cnt; i++)
        cout << int_arr[i] << " ";
    cout << endl;

    delete [] int_arr;
}