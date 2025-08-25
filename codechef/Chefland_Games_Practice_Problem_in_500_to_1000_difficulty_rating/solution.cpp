#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int R1, R2, R3, R4;
        cin >> R1 >> R2 >> R3 >> R4;
        if (R1 + R2 + R3 + R4 == 0) {
            cout << "IN" << endl;
        }
        else {
            cout << "OUT" << endl;
        }
    }
    return 0;

}