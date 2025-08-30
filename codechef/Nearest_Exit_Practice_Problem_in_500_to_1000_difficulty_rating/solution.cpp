#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= 51) {
            cout << "RIGHT" << endl;
        }
        else {
            cout << "LEFT" << endl;
        }
    }
    return 0;
}