#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int reverse = 0;
        while (n) {
            reverse = reverse * 10 + n % 10;
            n /= 10;

        }
        cout << reverse << endl;
    }


    return 0;

}