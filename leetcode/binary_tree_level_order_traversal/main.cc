#include "leetcode.h"
class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		int height = getHeight(root);
		vector<vector<int>> results(height);
		dfs(root, height - 1, results);
		return results;
	}

	void dfs(TreeNode* root, int level, vector<vector<int>>& results) {
		if (root == nullptr) return;

		results[level].push_back(root->val);

		dfs(root->left, level - 1, results);
		dfs(root->right, level - 1, results);
	}

	int getHeight(TreeNode* root) {
		if (root == nullptr) return 0;

		return max(getHeight(root->left), getHeight(root->right)) + 1;
	}
};
