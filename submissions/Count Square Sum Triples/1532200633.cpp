# Title: Count Square Sum Triples
# Submission ID: 1532200633
# Status: Accepted
# Date: February 5, 2025 at 04:07:10 PM GMT+5:30

class Solution {
public:
    int countTriples(int n) {
        int count = 0;
        for(int i = 1; i <=n; i++){
            for(int j = 1; j<=n; j++){
                for(int k = 1; k<= n; k++){
                    if(i*i + j*j == k*k){
                        count++;
                    }
                }
            }
        }
    return count;
    }
};