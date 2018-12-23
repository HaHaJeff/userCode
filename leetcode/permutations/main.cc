#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {

		vector<vector<int>> results;
		vector<int> result;

		backtrace(nums, results,  0);
		return results;
	}

	void backtrace(vector<int>& nums, vector<vector<int>>& results, int begin) {

		if (begin >= nums.size()) {
			results.push_back(nums);
			return;
		}

		for (int i = begin; i < nums.size(); i++) {
			swap(nums[begin], nums[i]);
			backtrace(nums, results, begin + 1);
			swap(nums[begin], nums[i]);
		}
	}
};

int main()
{
	Solution sol;
	vector<int> nums = { 1, 2, 3 };
	vector<vector<int>> results = sol.permute(nums);
	for (auto result : results) {
		std::cout << "[";
		for (auto num : result) {
			std::cout << num << " ";
		}
		std::cout << "]" << std::endl;
	}
}
