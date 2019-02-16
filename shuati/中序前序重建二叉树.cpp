#include "header.h"
// ����ǰ���ؽ�������
// ˼·���ݹ鷽ʽ�������������б���Ѱ��ǰ���б���ֵ��λ�ã��ֱ𹹽����ҽڵ�
/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution{
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