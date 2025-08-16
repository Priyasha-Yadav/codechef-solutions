# Title: Swapping Nodes in a Linked List
# Submission ID: 1734532035
# Status: Accepted
# Date: August 14, 2025 at 10:52:12 AM GMT+5:30

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        vector<int> vec;
        ListNode* ptr = head;
        while(ptr!=nullptr){
            vec.push_back(ptr->val);
            ptr = ptr->next;
        };
        ptr=head;
        swap(vec[k-1], vec[vec.size()-k]);
        for(int i = 0; i<vec.size(); i++){
            ptr->val = vec[i];
            ptr=ptr->next;
        }

        return head;

        
    }
};