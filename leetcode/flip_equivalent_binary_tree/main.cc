#include "leetcode.h"

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
	bool flipEquiv(TreeNode* root1, TreeNode* root2) {
		return flipTree(root1, root2);
	}

	bool flipTree(TreeNode* root1, TreeNode* root2) {
		if (root1 == nullptr && root2 == nullptr) {
			return true;
		}
		else if (root1 == nullptr || root2 == nullptr){
			return false;
		}

		if (root1->val != root2->val) {
			return false;
		}
		return (flipTree(root1->left, root2->left) && flipTree(root1->right, root2->right)) || (flipTree(root1->right, root2->left) && flipTree(root1->left, root2->right));
	}
};

