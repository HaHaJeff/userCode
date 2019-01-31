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
    void reorderList(ListNode* head) {
        
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return;
        ListNode* n1 = head;
        ListNode* n2 = head;
        ListNode* n3 = head;  
        
        // find the mid of list and split it
        while(n1 != nullptr && n2 != nullptr && n2->next != nullptr && n2->next->next != nullptr) {
            n1 = n1->next;
            n2 = n2->next->next;
        }
        n3 = n1->next;
        n1->next = nullptr;
        
        // reverse list
        n1 = n2 = n3;    
        if (n3->next != nullptr) {
            n2 = n3->next;
            n3 = n2->next;
            n1->next = nullptr;
            while(n1 != nullptr && n2 != nullptr && n3 != nullptr) {
                n2->next = n1;
                n1 = n2;
                n2 = n3;
                n3 = n3->next;
            }
            n2->next = n1;
        }
        
        // n2 is the start of reverse list, merge two list
        n1 = head;
        while (n1 != nullptr && n2 != nullptr) {
            n3 = n2->next;
            n2->next = n1->next;
            n1->next = n2;
            n1 = n2->next;
            n2 = n3;
        }
    }
};
