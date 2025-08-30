#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int p, q, r, s;
        cin >> p >> q >> r >> s;
        int max_profit = max(max(p, q), max(r, s));
        if (p + q + r + s - max_profit >= max_profit) {
            cout << "NO" << endl;
        }
        else {
            cout << "YES" << endl;
        }
    }
    return 0;

}