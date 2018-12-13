#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

class Solution {
public:
	bool canPartitionKSubsets(vector<int>& nums, int k) {
		if (nums.empty() || k == 0) {
			return false;
		}

		visited_.resize(nums.size());
		int sum = std::accumulate(nums.begin(), nums.end(), 0);
		if (sum%k != 0) return false;
		return canPartitionKSubsets(nums, 0, k, 0, 0, sum / k);
	}

	bool canPartitionKSubsets(vector<int>& nums, int start, int k, int curSum, int curNum, int target) {
		if (k == 1) {
			return true;
		}
		if (curSum == target && curNum > 0) { return canPartitionKSubsets(nums, 0, k-1, 0, 0, target); }
		for (int i = start; i < nums.size(); ++i) {
			if (visited_[i] == 0) {
				visited_[i] = 1;
				if (canPartitionKSubsets(nums, i + 1, k, curSum + nums[i], curNum++, target)) return true;
				visited_[i] = 0;
			} 
		}
		return false;
	}

private:
	vector<int> visited_;
};

int main()
{
	vector<int> nums = { 4, 3, 2, 3, 5, 2, 1 };
	int k = 4;
	Solution sol;
	std::cout << sol.canPartitionKSubsets(nums, k) << std::endl;
}
