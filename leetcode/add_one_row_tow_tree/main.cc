/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
#include "leetcode.h"

//宽度优先
class Solution1 {
public:
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			auto node = new TreeNode(v);
			node->left = root;
			return node;
		};
		bfs(root, v, d);
		return root;
	}

	void bfs(TreeNode* root, int val, int dth) {
		vector<TreeNode*> cur, next;

		int d = 1;
		cur.push_back(root);

		while (d++ < dth - 1) {
			for (auto& node : cur) {
				if (node == nullptr) {
					continue;
				}
				next.push_back(node->left);
				next.push_back(node->right);
			}
			cur.swap(next);
			next.clear();
		}

		for (auto& node : cur) {
			if (node == nullptr) continue;
			auto left = new TreeNode(val);
			auto right = new TreeNode(val);
			left->left = node->left;
			right->right = node->right;
			node->left = left;
			node->right = right;

		}
	}
};

// 自底向上
class Solution2 {
public:
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		return dfs(root, v, d, true);
	}

	TreeNode* dfs(TreeNode* root, int v, int d, bool left) {
		if (d < 2) {
			auto newRoot = new TreeNode(v);
			if (left) newRoot->left = root;
			else newRoot->right = root;
			return newRoot;
		}
		if (root == nullptr) return nullptr;
		root->left = dfs(root->left, v, d - 1, true);
		root->right = dfs(root->right, v, d - 1, false);
		return root;
	}
};

//自底向上
class Solution {
public:
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			auto newRoot = new TreeNode(v);
			newRoot->left = root;
			return newRoot;
		}
		
		dfs(root, v, 1, d);
		return root;

	}

	void dfs(TreeNode* root, int v, int d, int limit) {
		if (d == limit - 1) {
			auto left = new TreeNode(v);
			auto right = new TreeNode(v);
			left->left = root->left;
			right->right = root->right;
			root->left = left;
			root->right = right;
			return;
		}

		dfs(root->left, v, d+1, limit);
		dfs(root->right, v, d + 1, limit);

	}
};
