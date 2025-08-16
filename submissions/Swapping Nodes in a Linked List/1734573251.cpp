# Title: Swapping Nodes in a Linked List
# Submission ID: 1734573251
# Status: Runtime Error
# Date: August 14, 2025 at 11:32:10 AM GMT+5:30

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
        ListNode* ptr = head;
        int Lsize = 0;
        ListNode* front = nullptr; 
        ListNode* rear = nullptr;
        while(ptr!=nullptr){
            Lsize++;
            ptr = ptr->next;

            if(Lsize == k-1){
                front = ptr;
            }
        }
        ptr = head;
        for(int i = 0; i< Lsize - k ;i++){
            ptr = ptr->next;
        }
        rear = ptr;

        int temp = front->val;
        front->val = rear-> val;
        rear->val = temp;

    return head;
    }
};