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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return head;
        ListNode* node1 = head;
        ListNode* node2 = head;
        int len = 1;
        while(node1->next != nullptr) {
            node1 = node1->next;
            len++;
        }
        
        node1->next = head;
        
        k = len - k%len;
        while(--k) {
            node2 = node2->next;
        }
                
        node1 = node2->next;
        node2->next = nullptr;
        return node1;
    }
};
