#include <vector>
#include <iostream>
using namespace std;

// 记录一个最小值和一个次小值
class Solution {
public:
	bool increasingTriplet(vector<int>& nums) {
		int min = INT_MAX, secMin = INT_MAX;

		for (auto num : nums) {
			if (num < min) {
				min = num;
			}
			else if (num < secMin) {
				secMin = min;
			}
			else {
				return true;
			}
		}
		return false;
 	}
};

int main()
{
	Solution sol;
	vector<int> nums = { 1,2,3,4,5 };
	std::cout << sol.increasingTriplet(nums) << std::endl;
}
