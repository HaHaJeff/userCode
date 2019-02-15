#include "header.h"

// 二维数组查找
//思路：从左下角开始遍历，缩小查找范围
class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		int row = array.size() - 1;
		int col = array[0].size() - 1;

		for (int i = row, j = 0; i >= 0 && j <= col;) {
			if (target == array[i][j]) return true;
			else if (target > array[i][j]) j++;
			else  i--;
		}
		return false;
	}
};
// 替换空格
// 思路：从后往前遍历
class Solution {
public:
	void replaceSpace(char *str, int length) {
		int space_cnt = 0;
		int old_end = 0, new_end = 0;
		while (str[old_end] != '\0') {
			if (str[old_end++] == ' ') space_cnt++;
		}
		int inc_size = space_cnt * 2;
		new_end = old_end + inc_size;
		while (old_end >= 0) {
			if (str[old_end] == ' ') {
				str[new_end--] = '0';
				str[new_end--] = '2';
				str[new_end--] = '%';
			}
			else {
				str[new_end--] = str[old_end];
			}
			--old_end;
		}
	}
};

// 中序前序重建二叉树
// 思路：递归方式构建，在中序列表中寻找前序列表中值的位置，分别构建左右节点
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.empty() || vin.empty()) return nullptr;
		int idx = 0;
		TreeNode* root = helper(pre, vin, idx, 0, pre.size() - 1);
		return root;
	}

	int find(const vector<int>& vin, int start, int end, int val) {
		int ret = 0;
		for (int i = start; i <= end; i++) {
			if (vin[i] == val) {
				ret = i;
				break;
			}
		}
		return ret;
	}

	TreeNode* helper(const vector<int>& pre, const vector<int>& vin, int& idx, int start, int end) {
		if (start > end) return nullptr;

		TreeNode* root = new TreeNode(pre[idx]);
		int mid = find(vin, start, end, root->val);
		idx++;
		root->left = helper(pre, vin, idx, start, mid - 1);
		root->right = helper(pre, vin, idx, mid + 1, end);
		return root;
	}
};
