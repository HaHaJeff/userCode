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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        int levelSize = 0;
        vector<vector<int>> results;
        queue<TreeNode*> q;
        if (root != nullptr) q.push(root);
        
        while (!q.empty()) {
            levelSize = q.size();
            vector<int> level;
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* ptr = q.front();
                if (ptr == nullptr) continue;
                if (ptr->left != nullptr) q.push(ptr->left);
                if (ptr->right != nullptr) q.push(ptr->right);
                level.push_back(ptr->val);
                q.pop();
            }
            results.push_back(level);
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
};
