# Title: Valid Parenthesis String
# Submission ID: 1532347020
# Status: Wrong Answer
# Date: February 5, 2025 at 06:55:43 PM GMT+5:30

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
        return (stack == 0 || stack + star == 0 || stack - star == 0);
};