#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		return lengthOfLISBinarySearch(nums);
	}
	int lengthOfLISDP(vector<int>& nums) {
		if (nums.empty()) return 0;
		vector<int> dp(nums.size(), 1);
		for (int i = 1; i < nums.size(); i++) {

			for (int j = 0; j < i; j++) {
				dp[i] = nums[i] > nums[j] ? max(dp[i], dp[j] + 1) : dp[i];
			}
		}

		int max = 0;
		for (int i = 0; i < nums.size(); i++) {
			max = dp[i] > max ? dp[i] : max;
		}

		return max;
	}

	//借助额外数组用以保证该数组类的数据为当前数子之前的递增子序列
	int lengthOfLISBinarySearch(vector<int>& nums) {
		if (nums.empty()) return 0;
		vector<int> inc{ nums[0] };

		for (int i = 1; i < nums.size(); i++) {
			int low = 0, high = inc.size(), mid = 0;
			while (low < high) {
				mid = (low + high) / 2;
				if (inc[mid] < nums[i]) {
					low = mid + 1;
				}
				else {
					high = mid;
				}
			}
			if (low == inc.size()) {
				inc.push_back(nums[i]);
			}
			else {
				inc[low] = nums[i];
			}
		}
		return inc.size();
	}
};

int main()
{
	Solution sol;
	vector<int> vec{ 10,9,2,5,3,7,101,18 };
	std::cout << sol.lengthOfLIS(vec) << std::endl;
}
