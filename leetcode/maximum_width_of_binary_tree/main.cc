class Solution {
public:
	int widthOfBinaryTree(TreeNode* root) {
		if (nullptr == root) return 0;
		vector<pair<TreeNode*, int>> cur, next;
		int maxDis = 1;
		cur.push_back(make_pair(root, 1));

		while (true) {
			for (auto iter : cur) {
				if (iter.first->left != nullptr) next.push_back(make_pair(iter.first->left, iter.second * 2));
				if (iter.first->right != nullptr) next.push_back(make_pair(iter.first->right, iter.second * 2 + 1));
			}
			maxDis = std::max(maxDis, cur.back().second - cur.front().second + 1);
			if (next.empty()) break;
			cur = next;
			next.clear();
		}
        return maxDis;
	}
};
