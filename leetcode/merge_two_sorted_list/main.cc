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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr || l2 == nullptr) return l1 ? l1 : l2;
        ListNode* node1 = l1;
        ListNode* node2 = l2;
        ListNode* tail = new ListNode(0);
        while (node1 != nullptr && node2 != nullptr) {
            if (node1->val < node2->val) {
                tail->next = node1;
                node1 = node1->next;
            } else {
                tail->next = node2;
                node2 = node2->next;
            }
            tail = tail->next;
        }
        tail->next = node1 ? node1 : node2;
        
        return l1->val < l2->val ? l1 : l2;
    }
};
