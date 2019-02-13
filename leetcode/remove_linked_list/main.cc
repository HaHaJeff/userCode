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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode** prev = &head;
        
        ListNode* cur = nullptr;
        while((cur = *prev) != nullptr) {
            
            while (cur != nullptr && cur->val == val) {
                auto del = cur;
                cur = cur->next;
                *prev = cur;
                delete del;
            }
            if (cur != nullptr)
                prev = &cur->next;
        }
        return head;
        
    }
};
