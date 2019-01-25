#include "leetcode.h"

class Solution {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		return dfs(head, nullptr);
	}

	TreeNode* dfs(ListNode* head, ListNode* tail) {
		if (head == tail) {
			return nullptr;
		}

		ListNode* slow = head;
		ListNode* fast = head;

		while (fast != tail && fast->next != tail) {
			slow = slow->next;
			fast = fast->next->next;
		}

		TreeNode* root = new TreeNode(slow->val);
		TreeNode* left = dfs(head, slow);
		TreeNode* right = dfs(slow->next, tail);

		root->left = left;
		root->right = right;

		return root;
	}
};
