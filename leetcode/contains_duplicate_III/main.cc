#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				long long ik = abs((long long)j - i);
				long long it = abs((long long)nums[j] - nums[i]);
				if (it <= (long long)t && ik <= (long long)k) {
					return true;
				}
			}
		}
		return false;
	}
};

int main()
{
	vector<int>nums = { -1, INT_MAX };
	Solution sol;

	std::cout << sol.containsNearbyAlmostDuplicate(nums, 1, INT_MAX) << std::endl;
}s
