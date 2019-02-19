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
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* next = nullptr;
        ListNode* prev = nullptr;
        while(pHead) {
            next = pHead->next;
            pHead->next = prev;
            prev = pHead;
            pHead = next;
        }
        return prev;
    }
};
