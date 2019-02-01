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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* prev = nullptr;
        ListNode* next = head->next;
        
        while(next != nullptr) {
            head->next = prev;
            prev = head;
            head = next;
            next = next->next;
        }
        head->next = prev;
        return head;
        
        //return recurList(nullptr, head);
    }
    
    ListNode* recurList(ListNode* prev, ListNode* cur) {
        if (cur == nullptr) return prev;
        auto next = cur->next;
        cur->next = prev;
        return recurList(cur, next);
    }
};
