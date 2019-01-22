#include "leetcode.h"
class Solution {
public:
	int minCameraCover(TreeNode* root) {
		int res = 0;
		// 如果root节点没有被覆盖，则需要在root节点处增加一个照相机
		return dfs(root, res) < 1 ? 1 + res : +res;
	}

	int dfs(TreeNode* root, int &res) {
		if (root == nullptr) {
			return 2;
		}

		int left = dfs(root->left, res);
		int right = dfs(root->right, res);

		// 叶子节点的父节点
		if (left == 0 || right == 0) {
			res++;
			return 1;
		}

		// 如果左节点或右节点被放置了照相机，则说明当前root已经被覆盖了，返回2；
		// 否则返回0，相当于不考虑root以下的节点了（当前root重新成为叶子节点）
		return left == 1 || right == 1 ? 2 : 0;
	}
};
