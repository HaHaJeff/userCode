#include "leetcode.h"
class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		helper(root);
		return results;
	}

	string helper(TreeNode* root) {
		if (root == nullptr) return "- ";

		string id = to_string(root->val) + " ";
		id += helper(root->left);
		id += helper(root->right);

		if (++counts[id] == 2) {
			results.push_back(root);
		}
		return id;

	}

private:
	unordered_map<string, int> counts;
	vector<TreeNode*> results;
};
