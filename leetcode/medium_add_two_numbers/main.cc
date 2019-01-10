#include "leetcode.h"

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

		vector<int> nums1;
		vector<int> nums2;
		ListNode *head1 = l1, *head2 = l2;
		while (head1 != nullptr) {
			nums1.push_back(head1->val);
			head1 = head1->next;
		}

		while (head2 != nullptr) {
			nums2.push_back(head2->val);
			head2 = head2->next;
		}

		int carry = 0;
		ListNode* head = nullptr, *node = nullptr;
		for (int i = nums1.size() - 1, j = nums2.size() - 1; i >= 0 || j >= 0 || carry > 0; i--, j--) {
			int sum = carry;
			if (i >= 0) {
				sum += nums1[i];
			}
			if (j >= 0) {
				sum += nums2[j];
			}
			
			carry = sum / 10;
			sum %= 10;

			node = new ListNode(sum);
			node->next = head;
			head = node;
		}

		return head;
	}
};
