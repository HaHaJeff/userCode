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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node = head;
        
        while(node && node->next) {
            if (node->val == node->next->val) {
                auto del = node->next;
                node->next = del->next;
                delete del;
            } else node = node->next;
        }
        return head;
    }
};
