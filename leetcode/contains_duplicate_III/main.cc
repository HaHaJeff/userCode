class Solution {
public:
	bool help(const std::set<long long>& window, long long val, long long target) {
		// numx[i] - x <= t ====> x >= nums[i] - t
		auto pos = window.lower_bound(val - target);
		// nums[i] - x >= -t ===> x - nums[i] <= t
		if (pos != window.end() && *pos - val <= target) return true;
		return false;
	}

	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		if (k == 0) return false;
		std::set<long long> windows;
		int size = nums.size();
		long long lk = static_cast<long long>(k);
		long long lt = static_cast<long long>(t);

		for (int i = 0; i < size; ++i) {
			if (i > k) windows.erase(nums[i - k - 1]);
			// |nums[i] - x| <= t  =====>  nums[i] - x >= -t && nums[i] - x <= t
			if (help(windows, static_cast<long long>(nums[i]), lt)) {
				return true;
			}
			windows.insert(nums[i]);
		}
		return false;
	}
};

