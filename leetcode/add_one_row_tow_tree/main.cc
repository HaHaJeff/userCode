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
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            auto node = new TreeNode(v);
            node->left = root;
            return node;
        };
        bfs(root, v, d);
        return root;
    }
    
    void bfs(TreeNode* root, int val, int dth) {
        vector<TreeNode*> cur, next;
        
        int d = 1;
        cur.push_back(root);
        
        while (d++ < dth - 1) {
            for (auto& node : cur) {
                if (node == nullptr) { 
                    continue;
                }
                next.push_back(node->left);
                next.push_back(node->right);
            }
            cur.swap(next);
            next.clear();
        }

        for (auto& node : cur) {
            if (node == nullptr) continue;
            auto left = new TreeNode(val);
            auto right = new TreeNode(val);
            left->left = node->left;
            right->right = node->right;
            node->left = left;
            node->right = right;

        }
    }
};
