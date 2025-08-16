# Title: Swapping Nodes in a Linked List
# Submission ID: 1734595159
# Status: Accepted
# Date: August 14, 2025 at 11:52:27 AM GMT+5:30

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* ptr = head;
        int Lsize = 0;
        ListNode* front = nullptr; 
        ListNode* rear = nullptr;
        

        while(ptr != nullptr) {
            Lsize++;
            if(Lsize == k) {
                front = ptr;
            }
            ptr = ptr->next;
        }
        

        ptr = head;
        for(int i = 0; i < Lsize - k; i++) {
            ptr = ptr->next;
        }
        rear = ptr;
        

        swap(front->val, rear->val);

        return head;
    }
};