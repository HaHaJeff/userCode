// 记录一个最小值和一个次小值
// 只需要保证在num之前按序出现国min和secMin即可
class Solution {
public:
	bool increasingTriplet(vector<int>& nums) {
		int min = INT_MAX, secMin = INT_MAX;

		for (auto num : nums) {
			if (num <= min) {
				min = num;
			}
			else if (num <= secMin) {
				secMin = num;
			}
			else {
                std::cout << min << " " << secMin << " " << num << std::endl;
				return true;
			}
		}
		return false;
 	}
};

