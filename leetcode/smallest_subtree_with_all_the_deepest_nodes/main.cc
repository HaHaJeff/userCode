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
	TreeNode* subtreeWithAllDeepest(TreeNode* root) {
		TreeNode* maxSubtree = nullptr;

		auto ret = subtree(root);

		return ret.second;
	}

	std::pair<int, TreeNode*> subtree(TreeNode* root) {
		if (root == nullptr) {
			return{ 0, nullptr };
		}

		auto left = subtree(root->left);
		auto right = subtree(root->right);

		return{ max(left.first, right.first) + 1, left.first == right.first ? root : left.first > right.first ? left.second : right.second };

	}
};
