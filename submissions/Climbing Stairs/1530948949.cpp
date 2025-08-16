# Title: Climbing Stairs
# Submission ID: 1530948949
# Status: Accepted
# Date: February 4, 2025 at 04:57:10 PM GMT+5:30

class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;

        int prev2 = 1, prev1 = 2;
        int current = 0;

        for (int i = 3; i <= n; i++) {
            current = prev1 + prev2;  
            prev2 = prev1;            
            prev1 = current;          
        }

        return current;
    }
    
};