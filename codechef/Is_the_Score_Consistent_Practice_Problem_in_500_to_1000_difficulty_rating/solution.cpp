#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int c, d;
        cin >> c >> d;
        if (a <= c) {
            (b <= d) ? cout << "POSSIBLE" << endl: cout << "IMPOSSIBLE" << endl;

        }
        else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}