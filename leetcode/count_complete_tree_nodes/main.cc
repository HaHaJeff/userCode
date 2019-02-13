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
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        int hl = 0, hr = 0;
        
        for(auto node = root; node != nullptr; node = node->left) {hl++;}
        for(auto node = root; node != nullptr; node = node->right) {hr++;}
        
        if (hl == hr) {
            return pow(2, hl) - 1;
        }  else {
            return 1 + countNodes(root->left) + countNodes(root->right);
        }
    }
};
