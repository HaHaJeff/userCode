class Solution {
public:

	int findBottomLeftValue(TreeNode* root) {
		int maxDeepth = INT_MIN;
		int maxValue = 0;

		dfs(maxDeepth, maxValue, 0, root);
		return maxValue;
	}

	void dfs(int& maxDeepth, int& maxValue, int deepth, TreeNode* root) {
		if (root == nullptr) {
			return;
		}

		dfs(maxDeepth, maxValue, deepth + 1, root->left);
		dfs(maxDeepth, maxValue, deepth + 1, root->right);

		if (deepth > maxDeepth) {
			maxDeepth = deepth;
			maxValue = root->val;
		}
	}
};

