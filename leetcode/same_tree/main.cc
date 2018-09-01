
class Solution {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		bool ret = recur(p, q);
		return ret;
	}

	bool recur(TreeNode* root1, TreeNode* root2) {
		if (root1 == nullptr && root2 == nullptr) {
			return true;
		}
		if (root1 == nullptr || root2 == nullptr) {
			return false;
		}

		if (root1->val == root2->val) {
			return recur(root1->left, root2->left) && recur(root1->right, root2->right);
		}
		else {
			return false;
		}
	}
};
