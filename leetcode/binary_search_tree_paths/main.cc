#include "leetcode.h"

class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> results;
		dfs(root, results, "");
	}

	void dfs(TreeNode* root, vector<string>& results, string str) {
		if (root == nullptr) {
			results.push_back(str);
		}

		dfs(root->left, results, str + to_string(root->val));
		dfs(root->right, results, str + to_string(root->val));
	}
};

class Solution1 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

		if (root->val > p->val && root->val > q->val)
			return lowestCommonAncestor(root->left, p, q);

		if (root->val < p->val && root->val < q->val)
			return lowestCommonAncestor(root->right, p, q);

		return root;
	}
};
