#include "zombie.h"

int main() {
    int n;

    cout << "Enter coins >> ";
    cin >> n;
    cout << endl;

    GameManager gm(n);

    gm.info_total_win();

    return 0;
}