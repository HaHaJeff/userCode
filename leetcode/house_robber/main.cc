#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int rob(vector<int>& nums) {
		vector<int> dp(nums.size(), 0);

		dp[0] = nums[0];
		dp[1] = nums[1];
		dp[2] = dp[0] + nums[2];
		for (int i = 3; i < nums.size(); i++) {
			dp[i] = std::max(std::max(nums[i] + dp[i - 2], nums[i] + dp[i - 3]), dp[i-1]);
		}

		return dp[nums.size() - 1];
	}
};

int main()
{
	Solution sol;
	vector<int> nums = {1,2,3,1};
	int num = sol.rob(nums);
	std::cout << num << std::endl;
}
