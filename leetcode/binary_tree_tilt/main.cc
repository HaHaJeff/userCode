#include "leetcode.h"

class Solution {
public:
	int findTilt(TreeNode* root) {
		int result = 0;
		dfs(root, result);
		return result;
	}

	int dfs(TreeNode* root, int& result) {
		if (root == nullptr) {
			return 0;
		}

		int left = dfs(root->left, result);
		int right = dfs(root->right, result);
		result += abs(left - right);
		return left + right + root->val;
	}
};
