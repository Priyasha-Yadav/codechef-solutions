# Title: Pow(x, n)
# Submission ID: 1533002048
# Status: Runtime Error
# Date: February 6, 2025 at 07:06:57 AM GMT+5:30

/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function(x, n) {
    if(n == 0){
        return 1;
    }
    if (n < 0) {
        return 1 / myPow(x, -n);  
    }
    
    return myPow(x,n-1) * x;
};