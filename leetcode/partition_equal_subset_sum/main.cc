#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
	bool backTrack(vector<int>& nums, int start, int target) {
		if (target <= 0) return target == 0;

		for (int i = start; i < nums.size(); i++) {
			if (backTrack(nums, i + 1, target - nums[i])) return true;
		}

		return false;
	}

	//0-1背包选或不选
	//dp[i][j] = dp[i-1][j-nums[i]](选)   dp[i][j] = dp[i-1][j](不选)
	bool dp(vector<int>& nums, int start, int target) {
		vector<vector<int>> dp(nums.size()+1, vector<int>());
		for (auto& item : dp) {
			item.resize(target + 1);
		}
		
		dp[0][0] = true;

		for (int i = 1; i <= nums.size(); ++i) {
			dp[i][0] = true;
		}

		for (int j = 1; j <= target; ++j) {
			dp[0][j] = false;
		}

		for (int i = 1; i <= nums.size(); ++i) {
			for (int j = 1; j <= target; ++j) {
				
				dp[i][j] = dp[i - 1][j];
				if (j >= nums[i-1])
					dp[i][j]  = dp[i][j] || dp[i - 1][j - nums[i-1]];
			}
		}

		return dp[nums.size()][target];
	}

	bool canPartition(vector<int>& nums) {	
		int sums = accumulate(nums.begin(), nums.end(), 0);
		if (sums & 1) return false;
		return dp(nums, 0, sums / 2);
	}
};

int main()
{
	Solution sol;
	std::vector<int> nums = { 1, 3, 3, 5 };
	std::cout << sol.canPartition(nums) << std::endl;
}
