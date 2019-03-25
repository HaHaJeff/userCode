# valid binary search tree
**思路：采用递归的方式，root->left->val < root->val && root->right->val > root->val**
**但是这种思路有问题，因为只考虑了局部，而没有考虑全局**
``` cpp
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
```

**思路：**
- 左左子树：所有节点都要小于根节点
- 左右子树：所有节点都要大于当前根节点，但是要小于根节点
- 右右子树：所有节点都要大于根节点
- 右左子树：所有节点都要小于当前根节点，但是要大于根节点
``` cpp
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
```

## two sum iv input as a bst
**在一个平衡二叉树中找到两数之和为num**
- 方法1：采用递归的是， O(nh)，h最好情况为lgn，最坏为n，额外空间复杂度O(h)
**思路：采用递归的方式对每一个节点都进行判断，每次判断相当于在整颗数中寻找满足val == k-cur->val（寻找的过程中可以利用bst特性加速）**
``` cpp
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        return dfs(root, root, k);
    }
    bool dfs(TreeNode* root, TreeNode* cur, int val) {
        if (cur == nullptr) return false;
        return search(root, cur, val - cur->val) || dfs(root, cur->left, val) || dfs(root, cur->right, val);
    }
    bool search(TreeNode* root, TreeNode* cur, int val) {
        if (root == nullptr) return false;
        return root->val == val && root != cur || (root->val > val && search(root->left, cur, val)) || (root->val < val && search(root->right, cur, val));
    }
};
```
- 方法2：采用中序遍历+双指针查找 O(n)，额外空间复杂度O(n)
``` cpp
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        vector<int> v;
        while (cur || !s.empty()) {
            while(cur) {
                s.push(cur);
                cur = cur->left;
            }
            if (!s.empty()) {
                cur = s.top();
                s.pop();
                v.push_back(cur->val);
                cur = cur->right;
            }
        }
        int i = 0, j = v.size()-1;
        while (i < j) {
            if (v[i] + v[j] == k) return true;
            v[i] + v[j] < k ? i++ : j--;
        }
        return false;
    }
};
```
- 方法3：采用set对已经遍历过的值进行存储，方法具有普适性，时间复杂度O(n)，空间复杂度O(n)
``` cpp
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> s;
        return dfs(root, s, k);
    }
    bool dfs(TreeNode* root, unordered_set<int>& s, int k) {
        if (root == nullptr) return false;
        if (s.count(k-root->val)) { return true;}
        s.insert(root->val);
        return dfs(root->left, s, k) || dfs(root->right, s, k);
    }
};
```