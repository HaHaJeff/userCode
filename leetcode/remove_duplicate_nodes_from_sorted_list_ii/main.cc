/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        auto slow = head, fast = head;
        
        while (fast != nullptr && fast->next != nullptr ) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) break;
        }
        
        if (fast == nullptr) return nullptr; 
        slow = head;
        
        while (fast != slow && fast && slow) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
