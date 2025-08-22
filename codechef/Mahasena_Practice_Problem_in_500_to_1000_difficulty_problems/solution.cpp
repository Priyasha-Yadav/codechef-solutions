#include <bits/stdc++.h>

using namespace std;

int main() {
    int t, even = 0, odd = 0;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2 == 0) {
            even++;
        }
        else {
            odd++;
        }
    }
    if (even > odd) {
        cout << "READY FOR BATTLE" << endl;
    }
    else {
        cout << "NOT READY" << endl;
    }

    return 0;

}