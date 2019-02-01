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
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* mid = findMid(head);
        ListNode* next = mid->next;
        mid->next = nullptr;
        
        ListNode* head1 = sortList(head);
        ListNode* head2 = sortList(next);
        
        return merge(head1, head2);
    }
    
    ListNode* findMid(ListNode* head) {
        auto slow = head;
        auto fast = head;
        
        while(fast != nullptr && fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode dummy(0);
        auto tail = &dummy;
        while (head1 != nullptr && head2 != nullptr) {
            if (head1->val < head2->val) {
                tail->next = head1;
                head1 = head1->next;
            } else {
                tail->next = head2;
                head2 = head2->next;
            }
            tail = tail->next;
        }
        
        if (head1 != nullptr) {
            tail->next = head1;
        }
        if (head2 != nullptr) {
            tail->next = head2;
        }        
        return dummy.next;
    }
};

