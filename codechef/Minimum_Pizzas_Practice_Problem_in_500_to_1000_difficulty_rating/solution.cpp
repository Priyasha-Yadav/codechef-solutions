#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x, n;
        cin >> x >> n;
        if (float(x * n) / 4 == int(x * n) / 4) {
            cout << (x * n) / 4 << endl;
        }
        else {
            cout << ((x * n) / 4) + 1 << endl;
        }
    }
    return 0;
}