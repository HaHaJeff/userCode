#include "leetcode.h"

class Solution {
public:
	TreeNode* pruneTree(TreeNode* root) {
		if (nullptr == root) {
			return nullptr;
		}

		root->left = pruneTree(root->left);
		root->right = pruneTree(root->right);

		if (nullptr == root->left && nullptr == root->right && root->val == 0) {
			return nullptr;
		}
		return root;
	}
};
