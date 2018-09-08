#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

// dp[i][j]: 以i为开始，j为结束的满足条件的最大subset
// if (nums[j]%nums[i] == 0) dp[i][j] = dp[i][j-1] + 1
// else dp[i][j] = dp[i][j-1]
class Solution {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		if (nums.empty()) {
			return vector<int>();
		}
		sort(nums.begin(), nums.end());
		const int size = nums.size();
		int *dp = new int[size]();
		for (int i = 0; i < size; ++i) dp[i] = 1;
		for (int i = 0; i < size; ++i) {
			for (int j = i+1; j < size; ++j) {
				if (nums[j] % nums[i] == 0) {
					dp[j] = std::max(dp[i] + 1, dp[j]);
				}
			}
		}

		int max_dp = dp[0];
		int max_index = 0;
		for (int i = 1; i < size; i++)
		{
			if (dp[i] > max_dp){
				max_index = i;
				max_dp = dp[i];
			} 
		}

		for (int i = 0; i < size; i++) {
			std::cout << dp[i] << " ";
		}
		std::cout << std::endl;
		vector<int> results;
		int tmp = dp[max_index];

		for (int i = max_index; i >= 0; i--) {
			if (nums[max_index] % nums[i] == 0 && tmp == dp[i]) {
				results.insert(results.begin(), nums[i]);
				tmp -= 1;
			}
		}

		delete[]dp;
		return results;;
	}
};

int main()
{
	vector<int> nums{1,2,3,4,5,6,7,8};
	Solution sol;
	vector<int> results = sol.largestDivisibleSubset(nums);
	std::copy(results.begin(), results.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
