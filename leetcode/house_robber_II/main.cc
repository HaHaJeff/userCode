#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int rob(vector<int>& nums) {
		vector<int> dp1(nums.size() - 1, 0);
		vector<int> dp2(nums.size() - 1, 0);
		if (nums.empty()) return 0;
		if (nums.size() == 1) return nums[0];

		dp1[0] = nums[0];
		dp1[1] = std::max(nums[0], nums[1]);

		if (nums.size() == 2) return dp1[1];

		dp2[0] = nums[1];
		dp2[1] = std::max(nums[1], nums[2]);

		for (int i = 2; i < nums.size() - 1; i++) {
			dp1[i] = std::max(nums[i] + dp1[i - 2], dp1[i - 1]);
			dp2[i] = std::max(nums[i + 1] + dp2[i - 2], dp2[i - 1]);
		}

		return std::max(dp1[nums.size() - 2], dp2[nums.size() - 2]);
	}
};

//int main()
//{
//	Solution sol;
//	vector<int> nums = { 1,2,3,4,5,2,7,1,6 };
//	int num = sol.rob(nums);
//	std::cout << num << std::endl;
//}
