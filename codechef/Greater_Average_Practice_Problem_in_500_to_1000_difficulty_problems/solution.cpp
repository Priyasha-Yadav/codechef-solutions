#include <bits/stdc++.h>
using namespace std;

int main() {
    // your code goes here
    int t;
    cin>>t;
    while(t--){
        int A, B, C;
        float avg;
        cin>>A>>B>>C;
        avg = float (A+B)/2;
        
        if(avg>C){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
        
    }
    return 0;

}
