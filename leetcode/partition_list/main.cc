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
    ListNode* partition(ListNode* head, int x) {
        ListNode less(0), great(0);
        ListNode* pLess = &less;
        ListNode* pGreat = &great;
        
        while(head) {
            if(head->val < x) {
                pLess = pLess->next = head;
            } else {
                pGreat = pGreat->next =head;
            }
            head = head->next;
        }
        pGreat->next = nullptr;
        pLess->next = great.next;
        
        return less.next;
    }
};
