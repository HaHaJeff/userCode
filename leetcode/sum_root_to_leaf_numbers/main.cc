/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
	int sumNumbers(TreeNode* root) {
		return calcSum(root, 0);
	}

	int calcSum(TreeNode* root, int sum) {
		if (root == nullptr) return 0;
		if (root->left == nullptr && root->right == nullptr) return root->val + sum * 10;
		return calcSum(root->left, sum * 10 + root->val) + calcSum(root->right, sum * 10 + root->val);
	}
};
