#include "leetcode.h"

#include <vector>
#include <iostream>
#include <algorithm>
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
	typedef vector<int>::iterator Iter;
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty()) return nullptr;

		preorder_ = preorder;
		inorder_ = inorder;

		int i = 0;
		TreeNode* root = recur(i, 0, preorder_.size()-1);
		return root;

	}

	int find_(int start, int end, int val) {
		int ret = 0;
		for (int i = start; i <= end; ++i) {
			if (inorder_[i] == val) {
				ret = i;
				break;
			}
		}
		return ret;
	}

	TreeNode* recur(int& pre_idx, int start, int end) {
		if (start > end) {
			return nullptr;
		}

		TreeNode* root{ new TreeNode(preorder_[pre_idx]) };
		int mid = find_(start, end, preorder_[pre_idx++]);

		root->left = recur(pre_idx, start, mid - 1);
		root->right = recur(pre_idx, mid + 1, end);
		return root;
	}
private:
	vector<int> preorder_;
	vector<int> inorder_;
};

int main()
{

	Solution sol;

	vector<int> preorder{3, 6, 9};
	vector<int> inorder{ 6, 3, 9};

	TreeNode* root = sol.buildTree(preorder, inorder);

}
