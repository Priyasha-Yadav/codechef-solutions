# Title: Reverse Linked List
# Submission ID: 1731067559
# Status: Accepted
# Date: August 11, 2025 at 03:29:31 PM GMT+5:30

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
    ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;

    while (curr != nullptr) {
        next = curr->next; 
        curr->next = prev;  
        prev = curr;        
        curr = next;
    };

    return prev;  
};
    
};