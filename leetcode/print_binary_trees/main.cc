#include "leetcode.h"


/*
Input:
		1
	   / \
	  2   5
	 /
	3
   /
  4
Output:
[["", "", "", "", "", "", "", "1", "", "", "", "", "", "", ""]
["", "", "", "2", "", "", "", "", "", "", "", "5", "", "", ""]
["", "3", "", "", "", "", "", "", "", "", "", "", "", "", ""]
["4", "", "", "", "", "", "", "", "", "", "", "", "", "", ""]]
*/
// 每一行相当于宽度为2^height-1的数组，在特定位置插入节点值
class Solution {
public:
	vector<vector<string>> printTree(TreeNode* root) {
		if (root == nullptr) return results;
		int height = getHeight(root), width = pow(2, height) - 1;
		results.resize(height);
		for (auto& result : results) {
			result.resize(width);
		}
		helper(root, 0, width-1, 0, height);
		return results;
	}

	void helper(TreeNode* node, int i, int j, int cur, int height) {
		if (node == nullptr || cur == height) {
			return;
		}

		results[cur][(i + j) / 2] = to_string(node->val);
		helper(node->left, i, (i + j) / 2, cur + 1, height);
		helper(node->right, (i + j) / 2 + 1, j, cur + 1, height);
	}

	int getHeight(TreeNode* node) {
		if (node == nullptr) { return 0; }
		int left = getHeight(node->left) + 1;
		int right = getHeight(node->right) + 1;
		return max(left, right);
	}

private:
	vector<vector<string>> results;
};
