#include "leetcode.h"
class Solution {
public:
	vector<int> postorder(Node* root) {
		vector<int> result;
		if (root == nullptr) return result;
		helper(root, result);
		return result;

	}

	void helper(Node* root, vector<int>& result) {
		if (root == nullptr) {
			return;
		}
		for (auto node : root->children) {
			helper(node, result);
		}
		result.push_back(root->val);
	}
};
