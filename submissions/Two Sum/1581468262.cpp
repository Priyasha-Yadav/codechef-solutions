# Title: Two Sum
# Submission ID: 1581468262
# Status: Accepted
# Date: March 21, 2025 at 09:24:51 PM GMT+5:30

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
vector<int> result;
        for(int i = 0; i < nums.size(); i++){
            for(int j = i+1; j<nums.size(); j++){
                if(nums[i]+nums[j]==target){
result.push_back(i);
result.push_back(j);
 return result;
                }
            }
        }
    return result;
    }    
    
};