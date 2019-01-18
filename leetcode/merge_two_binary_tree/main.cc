#include "leetcode.h"

class Solution {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		return dfs(t1, t2);
	}

	TreeNode* dfs(TreeNode* n1, TreeNode* n2) {
		if (n1 != nullptr && n2 != nullptr) {
			n1->val += n2->val;
			n1->left = dfs(n1->left, n2->left);
			n1->right = dfs(n1->right, n2->right);
		}

		return n1 == nullptr ? n2 : n1;
	}
};
