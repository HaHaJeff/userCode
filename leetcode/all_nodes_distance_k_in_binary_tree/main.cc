#include "leetcode.h"

class Solution {
public:
	map<TreeNode*, TreeNode*> parent_;
	set<TreeNode*> visit_;

	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		vector<int> result;

		findParent(root);
		dfs(target, result, K);
		return result;
	}

	void findParent(TreeNode* node) {
		if (nullptr == node) {
			return;
		}
		
		if (node->left != nullptr) {
			parent_[node->left] = node;
			findParent(node->left);
		}

		if (node->right != nullptr) {
			parent_[node->right] = node;
			findParent(node->right);
		}
	}

	void dfs(TreeNode* node, vector<int>& result, int K) {
		if (visit_.find(node) != visit_.end()) {
			return;
		}

		visit_.insert(node);

		if (K == 0 && node != nullptr) {
			result.push_back(node->val);
			return;
		}

		if (node->left != nullptr) {
			dfs(node->left, result, K - 1);
		}

		if (node->right != nullptr) {
			dfs(node->right, result, K - 1);
		}

		if (parent_[node] != nullptr) {
			dfs(parent_[node], result, K - 1);
		}
	}
};
