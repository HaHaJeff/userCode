class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        pushAllLeft(root);
    }
    
    /** @return the next smallest number */
    int next() {
        auto t = st.top();
        st.pop();
        
        pushAllLeft(t->right);
        
        return t->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !st.empty();
    }
    
    void pushAllLeft(TreeNode* root) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
    }
    
private:
    stack<TreeNode*> st;
};
