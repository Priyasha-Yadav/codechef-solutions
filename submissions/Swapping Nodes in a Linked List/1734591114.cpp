# Title: Swapping Nodes in a Linked List
# Submission ID: 1734591114
# Status: Accepted
# Date: August 14, 2025 at 11:48:43 AM GMT+5:30

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
      ListNode* ptr = head;
      ListNode* temp = head;
      for(int i=0;i<k-1;i++){
        ptr=ptr->next;
      }
      ListNode* curr = ptr;
      while(ptr->next){
        temp=temp->next;
        ptr=ptr->next;
      }
      swap(curr->val,temp->val);
        return head;
    }
};
