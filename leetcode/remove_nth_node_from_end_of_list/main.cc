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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode* fast = head;
        ListNode** slow = &head;
        while (--n > 0) {
            fast = fast->next;
        }
        
        if (fast == nullptr) return head->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next;
            slow = &(*slow)->next;
        }
        ListNode* del = *slow;
        *slow = (*slow)->next;
        delete del;
        del = nullptr;
        
        return head;    
        
    }
};
