class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> results;
		dfs(root, results, "");
        return results;
	}

	void dfs(TreeNode* root, vector<string>& results, string str) {
        if (root == nullptr) return;
		if (root->left == nullptr && root->right == nullptr) {
			results.push_back(str+to_string(root->val));
            return;
		}

		dfs(root->left, results, str + to_string(root->val) + "->");
		dfs(root->right, results, str + to_string(root->val) + "->");
	}
};
