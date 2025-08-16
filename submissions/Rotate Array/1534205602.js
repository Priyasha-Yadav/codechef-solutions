# Title: Rotate Array
# Submission ID: 1534205602
# Status: Time Limit Exceeded
# Date: February 7, 2025 at 07:19:13 AM GMT+5:30

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var rotate = function(nums, k) {
    k = k % nums.length;
    for(let i=0;i<k;i++){
        let temp = nums[nums.length - 1 ];

        for(let j = nums.length - 1; j > 0; j--){
            nums[j] = nums[j-1]
        }

        nums[0] = temp;
    }

};