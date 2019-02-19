/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* fast = pListHead;
        while(fast != nullptr && k--) {
            fast = fast->next;
        }
        if (fast == nullptr && k != 0) pListHead = nullptr;
        while(fast != nullptr) {
            pListHead = pListHead->next;
            fast = fast->next;
        }
        return pListHead;
    }
};
