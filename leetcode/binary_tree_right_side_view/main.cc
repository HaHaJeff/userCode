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
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> q;
        vector<int> results;
        if (root == nullptr) return results;
        q.push(root);
        while(!q.empty()) {
            int size = q.size();
            results.push_back(q.back()->val);
            for (int i = 0; i < size; i++) {
                auto front = q.front();
                q.pop();
                if (front->left != nullptr) q.push(front->left);
                if (front->right != nullptr) q.push(front->right);
            }
        }
        return results;
    }
};
