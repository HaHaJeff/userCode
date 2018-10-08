// 0 1 2 3 4 5 6 7 8
// 1 2             3
// sort(vector)
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        int size = nums.size();
        int first = 0, second = 1, third = size - 1;
        int closestSum = nums[0] + nums[1] + nums[2];
        int currentSum = 0;
        std::sort(nums.begin(), nums.end());
        for (; first < size - 2; first++) {
            second = first + 1; third = size - 1;
            while (second < third) {
                currentSum = nums[first] + nums[second] + nums[third];
                if (currentSum == target)
                    return currentSum;
                closestSum = std::abs(target - closestSum) < std::abs(target - currentSum) ? closestSum : currentSum;

                if (currentSum < target) second++;
                else third--;
            }
        }

        return closestSum;
    }
};

int main()
{
	std::vector<int> nums{12, 8,9,-7,1,-2,3,-8,9};
	int target = 3;
	Solution sol;
	std::cout << sol.threeSumClosest(nums, target) << std::endl;
	std::copy( nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, "\t"));
}
