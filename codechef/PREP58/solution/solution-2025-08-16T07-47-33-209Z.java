class Solution
{
public:
    Node* detectCycle(Node* head)
    {
        if (!head || !head->next) return nullptr;

        Node* slow = head;
        Node* fast = head;

        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow; 
            }
        }
        return nullptr; 
    }
};
