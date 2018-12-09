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
	bool canPartition(vector<int>& nums) {
		
		int sums = accumulate(nums.begin(), nums.end(), 0);
		if (sums & 1) return false;
		return backTrack(nums, 0, sums / 2);
	}
};

int main()
{
	Solution sol;
	std::vector<int> nums = { 1, 2, 3, 5 };
	std::cout << sol.canPartition(nums) << std::endl;
}
