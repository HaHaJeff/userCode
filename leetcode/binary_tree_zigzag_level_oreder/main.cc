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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> results;
		if (nullptr == root) {
			return results;
		}

		queue<TreeNode*> parent;
		queue<TreeNode*> child;
		parent.push(root);
		bool flag{ false };

		while (!parent.empty()) {
			vector<int> per_level;
			child = parent;
            queue<TreeNode*> empty;
			parent.swap(empty);
			while (!child.empty()) {
				TreeNode* node = child.front();
				child.pop();
				per_level.push_back(node->val);

				if (nullptr != node->left) {
					parent.push(node->left);
				}
				if (nullptr != node->right) {
					parent.push(node->right);
				}
			}
			if (flag) {
				reverse(per_level.begin(), per_level.end());
			}
			flag = !flag;
			results.push_back(per_level);

		}
        return results;

	}
};
