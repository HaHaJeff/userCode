#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	// 记录index之前的最大值以及最小值，如果当前index为负值，则当前index的最大值为
	// index*min，否则index*max，由于是题目要求是子数组，所有index之前的最大值为
	// max(max_pre_index * index, min_pre_index*index, index)，最小值为 min(min_pre_index*index, max_pre_index*index, index);
	int maxProduct(vector<int>& nums) {
		int min{ nums[0] };
		int max{ min };
		int res{ min };
		for (int i = 1; i < nums.size(); i++) {

			max = std::max( std::max(max*nums[i], nums[i]), std::max(min*nums[i], nums[i]));
			min = std::min(std::min(max*nums[i], nums[i]), std::min(min*nums[i], nums[i]));

			res = std::max(max, res);
		}

		return res;
	}
};

int main()
{
	vector<int> nums = { 2, 3, -2, 4 , -10, 0, 1999};
	Solution sol;

	int res = sol.maxProduct(nums);

	std::cout << res << std::endl;
}s
