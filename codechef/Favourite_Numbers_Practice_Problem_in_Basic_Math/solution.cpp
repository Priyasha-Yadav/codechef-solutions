#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a;
        cin >> a;
        // your code goes here
        if (a % 7 == 0 && a % 2 == 0) {
            cout << "Alice" << endl;
        }
        else if (a % 9 == 0 && a % 2 == 1) {
            cout << "Bob" << endl;
        }
        else {
            cout << "Charlie" << endl;
        }
    }

}