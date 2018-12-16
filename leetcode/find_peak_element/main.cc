#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int findPeakElementForce(vector<int>& nums) {
		if (nums.empty() || nums.size() == 1) return 0;
		if (nums[0] > nums[1]) {
			return 0;
		}
		if (nums[nums.size() - 1] > nums[nums.size() - 2]) {
			return nums.size() - 1;
		}
		for (int i = 1; i < nums.size() - 1; i++) {
			if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i;
		}
		return 0;
	}
	// if mid > mid + 1, untilt to mid < mid + 1
	int findPeakElement(vector<int>& nums) {

		int low = 0;
		int high = nums.size() - 1;
		int mid = (low + high) / 2;
		while (low < high) {
			mid = (low + high) / 2;
			if (nums[mid] < nums[mid + 1]) low = mid + 1;
			else high = mid;
		}
		return low;
	}
};

int main()
{
	Solution sol;

	vector<int> nums = { 1, 2, 3, 1 };

	std::cout << sol.findPeakElement(nums) << std::endl;
}
