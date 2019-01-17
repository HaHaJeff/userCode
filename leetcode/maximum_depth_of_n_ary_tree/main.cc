class Solution {
public:
    int maxDepth(Node* root) {
        if (root == nullptr) return 0;
        if (root->children.empty()) return 1;
        int m = 0;
        for (auto child : root->children) {
            m = max(m, maxDepth(child) + 1);
        }
        return m;
    }
};
