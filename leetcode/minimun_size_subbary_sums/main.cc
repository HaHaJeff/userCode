#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int minSubArrayLen1(int s, vector<int>& nums) {

		int mini = INT_MAX;
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i; j < nums.size(); j++) {
				sum += nums[j];
				if (sum >= s) {
					mini = std::min(mini, j - i + 1);
					break;
				}
			}
			sum = 0;
		}
		return mini == INT_MAX ? 0 : mini;
	}

	//利用滑动窗口机制去除不必要的数据
	//最小窗口肯定无法向左滑动
	int minSubArrayLen(int s, vector<int>& nums) {
		int mini = INT_MAX;
		int sum = 0;
		int left = 0, right = 0;
		while (right < nums.size()) {
			while (sum < s && right < nums.size()) sum += nums[right++];

			if (sum >= s) {
				while (sum >= s && left < right) sum -= nums[left++];
				mini = std::min(mini, right - left + 1);
			}

		}
		return mini == INT_MAX ? 0 : mini;
	}
};
int main()
{
	std::vector<int> nums = { 1,2,3,4,5 };

	Solution sol;

	std::cout << sol.minSubArrayLen(11, nums) << std::endl;
}
