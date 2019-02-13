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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode** prev = &head;
        
        ListNode* cur = head;
        ListNode* next = cur;
        
        int k = n - m;
        while(--m) {
            prev = &cur->next;
            cur = cur->next;
        }
        
        while(k--) {
            next = cur->next;
            cur->next = next->next;
            next->next = *prev;
            *prev = next;
        }
        
        return head;
        
    }
};
