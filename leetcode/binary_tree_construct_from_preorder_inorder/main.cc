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
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty()) return nullptr;

		preorder_ = preorder;
		inorder_ = inorder;

		vector<int>::iterator root_val = preorder_.begin();
		TreeNode* root = recur(root_val, 0, preorder.size() - 1);
		return root;

	}

	TreeNode* recur(vector<int>::iterator root_val, int start, int end) {
		if (start == end) {
			return nullptr;
		}

		TreeNode* root{ new TreeNode(*root_val) };

		int mid = find(inorder_.begin()+start, inorder_.begin()+end, *root_val) - inorder_.begin();

		root->left = recur(root_val + 1, start, mid);
		root->right = recur(root_val + 1, mid + 1, end);

		return root;
	}

private:
	vector<int> preorder_;
	vector<int> inorder_;
};

int main()
{

	Solution sol;

	vector<int> preorder{3,9,20,15,7};
	vector<int> inorder{ 9,3,15,20,7};

	TreeNode* root = sol.buildTree(preorder, inorder);

}
