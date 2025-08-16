# Title: Valid Parenthesis String
# Submission ID: 1532948123
# Status: Wrong Answer
# Date: February 6, 2025 at 05:29:01 AM GMT+5:30

/**
 * @param {string} s
 * @return {boolean}
 */
var checkValidString = function(s) {
    let stack = 0;
        let star = 0;
        for(let i of s) {
            if(i == '(') {
                stack++;
            } else if(i == ')') {
                stack--;
            } else if(i == '*') {
                star++;
            }
        }
        if (stack == 0 || stack + star == 0){
            return true
        }
        else{
for(j = -star; j <= star; j++){
    if(stack-j == 0|| stack+j == 0){
        return true;
    }
}
        }
        return false
};