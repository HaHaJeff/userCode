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
// 后续遍历，先访问左节点，再访问右节点，最后访问根节点
// 非递归实现在于如何判断该节点的左右节点是否已经访问过
// 在循环中先push right节点，在push left节点，这样可以保证左节点在右节点之前被访问
// 可以打印的条件是：如果左右节点已经为空，或者左右节点已经访问过；
class Solution {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ret;
		stack<TreeNode*> s;
		if (root == NULL) return ret;

		TreeNode* cur = root;
		TreeNode* pre = NULL;

		s.push(root);

		while (!s.empty()) {
			cur = s.top();
			if ((cur->left == nullptr && cur->right == nullptr) || (pre != nullptr && (pre == cur->left || pre == cur->right))) {
				ret.push_back(cur->val);
				s.pop();
				pre = cur;  //标记已经访问过了
			}
			else {
				if (cur->right != nullptr) {
					s.push(cur->right);
				}
				if (cur->left != nullptr) {
					s.push(cur->left);
				}
			}
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

	vector<int> ret = sol.postorderTraversal(&root);

	for (auto item : ret) {
		std::cout << static_cast<char>(item) << "\t";
	}
	std::cout << std::endl;

}
