#include "leetcode.h"

// O(N) space  easy
class Solution {
public:
	vector<int> findDuplicates(vector<int>& nums) {
		std::vector<int> count(nums.size());
		std::vector<int> result;
		for (auto& num : nums) {
			count[num - 1]++;
		}

		for (int i = 0; i < count.size(); i++) {
			if (count[i] == 2)
				result.push_back(i + 1);
		}

		return result;

	}
};

// O(1) space medium
// 思路：把nums[i]对应位置的value置为相反值，如果该值出现过两次以为对应的位置的值会为正
class Solution {
public:
	vector<int> findDuplicates(vector<int>& nums) {

		std::vector<int> result;

		for (auto& num : nums) {
			nums[abs(num - 1)] = -nums[abs(num - 1)];
			if (nums[abs(num - 1)] > 0) {
				result.push_back(num);
			}
		}

		return result;

	}
};
