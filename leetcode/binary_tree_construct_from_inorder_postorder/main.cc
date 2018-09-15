#include <iostream>
#include <vector>
#include "leetcode.h"
using namespace std;

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
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		if (inorder.empty() || postorder.empty()) return nullptr;

		inorder_ = inorder;
		postorder_ = postorder;
		int i = postorder_.size() - 1;
		TreeNode* root = recur(i, 0, postorder_.size() - 1);
		return root;

	}
	inline int find_(int start, int end, int val) {
		int ret = 0;
		for (int i = start; i <= end; ++i) {
			if (inorder_[i] == val) {
				ret = i;
				break;
			}
		}
		return ret;
	}
	//相比中前序中序重建二叉树，中序后序重建需要确定后序遍历中的左右子树   mid-istart表示左子树有多少
	TreeNode* recur(int& pre_idx, int istart, int iend, int pstart, int pend) {
		if (istart > iend) {
			return nullptr;
		}

		TreeNode* root{ new TreeNode(postorder_[pend]) };
		int mid = find_(istart, iend, postorder_[pend]);

		root->left = recur(pre_idx, istart, mid - 1, pstart, pstart + mid-istart - 1);
		root->right = recur(pre_idx, mid + 1, iend, pstart + mid - istart, pend-1);
		return root;
	}
private:
	vector<int> inorder_;
	vector<int> postorder_;
};
