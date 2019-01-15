#include "leetcode.h"

// 1. 在同一侧，返回最上层的父节点即可
// 2. 不在同一侧，返回公共父节点
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

		if (nullptr == root || root == p || root == q) { 
			return root; 
		}

		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);

		return left == nullptr ? right : right == nullptr ? left : root;
	}
};
