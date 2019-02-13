class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode** prev = &head;
        ListNode* next = nullptr;
        ListNode* nNext = nullptr;
        while ((next = *prev) != nullptr && (nNext = next->next) != nullptr) {
            next->next = nNext->next;
            nNext->next = next;
            *prev = nNext;
            prev = &(next->next);
        }
        return head;
    }
};
