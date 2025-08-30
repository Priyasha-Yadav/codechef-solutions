#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        int count = 0;
        cin >> n;
        while (n--) {
            int d;
            cin >> d;
            if (d >= 1000) {
                count += 1;
            }
        }
        cout << count << endl;
    }
    return 0;

}