# Title: Greatest Common Divisor of Strings
# Submission ID: 1532208538
# Status: Accepted
# Date: February 5, 2025 at 04:16:25 PM GMT+5:30

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        return (str1+str2 == str2+str1) ? str1.substr(0,gcd(str1.length(), str2.length())) : "";
    }
};