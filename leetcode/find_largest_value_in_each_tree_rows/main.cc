#include "leetcode.h"

using namespace std;

class Solution {
public:
	vector<int> largestValues(TreeNode* root) {
		queue<TreeNode*> cur, next;

		vector<int> results;
		while (!cur.empty()) {

			int val = INT_MIN;
			while (!cur.empty()) {
				auto node = cur.front();
				if (node->left)
					next.push(node->left);
				if (node->right)
					next.push(node->right);
				val = max(val, node->val);
			}

			results.push_back(val);
			cur.swap(next);
		}

		return results;
	}

};
