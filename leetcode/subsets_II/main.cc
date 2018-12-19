#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<int> vec;
		vector<vector<int>> ret;
		std::sort(nums.begin(), nums.end());
		backTrace(nums, vec, ret, 0);
		return ret;
	}

	void backTrace(const vector<int>& nums, vector<int>& vec, vector<vector<int>>& ret, int begin) {
		ret.push_back(vec);
		for (int i = begin; i != nums.size(); ++i) {
			if (begin == i || nums[i] != nums[i - 1]) {
				vec.push_back(nums[i]);
				backTrace(nums, vec, ret, i + 1);
				vec.pop_back();
			}
		}
	}
};

int main()
{
	Solution sol;
	vector<int> nums = { 1, 2, 2 };
	vector<vector<int>> ret = sol.subsetsWithDup(nums);

	for (auto vec : ret) {
		for (auto num : vec) {
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
}
