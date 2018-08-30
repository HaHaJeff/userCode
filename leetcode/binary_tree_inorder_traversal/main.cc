// Definition for a binary tree node.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		stack<TreeNode*> s;
		if (root == NULL) return ret;

		TreeNode* cur = root;

		while (cur != nullptr || !s.empty()) {

			while (cur != nullptr) {
				s.push(cur);
				cur = cur->left;
			}
			
			cur = s.top();
			s.pop();
			ret.push_back(cur->val);
			cur = cur->right;
		}
		return ret;
	}
};

int main()
{
	TreeNode root{ static_cast<int>('a') };
	TreeNode level1_left{ static_cast<int>('b') };
	TreeNode level1_right{ static_cast<int>('g') };
	TreeNode level2_left{ static_cast<int>('c') };
	TreeNode level2_right{ static_cast<int>('f') };
	TreeNode level3_left{ static_cast<int>('d') };
	TreeNode level4_right{ static_cast<int>('e') };

	root.left = &level1_left;
	level1_left.left = &level2_left;
	level2_left.left = &level3_left;
	level3_left.right = &level4_right;
	level1_left.right = &level2_right;
	root.right = &level1_right;

	Solution sol;

	vector<int> ret = sol.inorderTraversal(&root);

	for (auto item : ret) {
		std::cout << static_cast<char>(item) << "\t";
	}
	std::cout << std::endl;

}
