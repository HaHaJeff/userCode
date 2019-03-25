/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution1 {
public:
    // 方法有问题：不能只是采用左子节点小于父节点或右子节点大于父节点
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        bool left = root->left == nullptr ? true : (root->left->val < root->val ? isValidBST(root->left) : false);
        bool right = root->right == nullptr ? true : (root->right->val > root->val ? isValidBST(root->right) : false);
        return left && right;
    }
};

// 左子树上：所有节点都要小于根节点
// 右子树上：所有节点都要大于根节点
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return dfs(root, nullptr, nullptr);
    }
    
    bool dfs(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(root == nullptr) return true;
        
        if(minNode != nullptr) {
            if (root->val <= minNode->val) return false;
        }
        if(maxNode != nullptr) {
            if (root->val >= maxNode->val) return false;
        }
        return dfs(root->left, minNode,root) && dfs(root->right, root, maxNode);
    }
};
