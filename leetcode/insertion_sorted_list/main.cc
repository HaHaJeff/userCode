#include "leetcode.h"

class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {

		ListNode* sentry = new ListNode(0);
		sentry->next = head;
		ListNode* pre = sentry;
		ListNode* cur = head;

		while (cur != nullptr) {
			if (cur->next != nullptr && cur->next->val < cur->val) {
				while (pre->next != nullptr && pre->next->val < cur->next->val) {
					pre = pre->next;
				}
				ListNode* preNext = pre->next;
				pre->next = cur->next;
				cur->next = cur->next->next;
				pre->next->next = preNext;
				pre = sentry;
			}
			else {
				cur = cur->next;
			}
		}
		return sentry->next;
	}
};
