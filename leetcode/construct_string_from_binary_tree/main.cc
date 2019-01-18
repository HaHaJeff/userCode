#include "leetcode.h"
class Solution {
public:
	string tree2str(TreeNode* t) {
		if (t == nullptr) return "";

		string ans = t->val + "";

		string left = tree2str(t->left);
		string right = tree2str(t->right);

		//leaf
		if (left == "" && right == "") {
		}
		else if (left == "") {
			ans = ans + "()" + "(" + right + ")";
		}
		else if (right == "") {
			ans = ans + "(" + left + ")";
		}
		else {
			ans = ans + "(" + left + ")" + "(" + right + ")";
		}
		return ans;
	}
};
