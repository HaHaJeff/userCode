/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool ret = false;
        if (pRoot1 != nullptr && pRoot2 != nullptr) {
            ret = isSubtree(pRoot1, pRoot2);
            if (!ret) {
                ret = HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
            }
        }
        return ret;
    }
    
    bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (pRoot2 == nullptr) return true;
        if (pRoot1 == nullptr) return false;
        if (pRoot1->val != pRoot2->val) return false;
        return isSubtree(pRoot1->left, pRoot2->left) && isSubtree(pRoot1->right, pRoot2->right);
    }
};
