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

class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) {
			return;
		}

		flatten(root->right);
		flatten(root->left);

		root->right = prev_;
		root->left = nullptr;

		prev_ = root;
	}

private:
	TreeNode* prev_;
};

