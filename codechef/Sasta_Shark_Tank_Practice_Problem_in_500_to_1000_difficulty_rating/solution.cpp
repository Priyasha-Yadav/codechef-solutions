#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (b * 5 == a * 10) {
            cout << "ANY" << endl;
        }
        else if (b * 5 > a * 10) {
            cout << "SECOND" << endl;
        }
        else {
            cout << "FIRST" << endl;

        }
    }
    return 0;

}