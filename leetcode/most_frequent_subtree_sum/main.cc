#include "leetcode.h"
using namespace std;

class Solution {
public:
	vector<int> findFrequentTreeSum(TreeNode* root) {
		vector<int> ret;

		int maxCnt = INT_MIN;
		int sum = subtreeSum(root, maxCnt);

		for (auto &result : results_) {
			if (result.second == maxCnt) ret.push_back(result.first);
		}

		return ret;

	}

	int subtreeSum(TreeNode* root, int& maxCnt) {
		int sum = 0;
		if (root != nullptr) {
			sum += root->val + subtreeSum(root->left, maxCnt) + subtreeSum(root->right, maxCnt);
			results_[sum]++;
			maxCnt = std::max(results_[sum], maxCnt);
		}
		return sum;

	}

private:
	std::map<int, int> results_;
};
