#include "leetcode.h"

using namespace std;
class Solution {
public:
	TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
		for (int i = 0; i < pre.size(); ++i) {
			index_[post[i]] = i;
		}

		return construct(pre, post, 0, pre.size() - 1, 0, post.size() - 1);
	}

	TreeNode* construct(const vector<int>& pre, const vector<int>& post, int s1, int e1, int s2, int e2) {
		TreeNode* root = new TreeNode(pre[s1]);
		if (s1 == e1)  return root;

		// 前序遍历中的值在后序遍历中的索引
		int idx = index_[pre[s1+1]];
		int len = idx - s2 + 1;
		root->left = construct(pre, post, s1+1, s1+len, s2, idx);
		if (idx + 1 == e2) return root;
		root->right = construct(pre, post, s1 + len + 1, e1, idx + 1, e2 - 1);

		return root;
	}

	std::map<int, int> index_;
};


