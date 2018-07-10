#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int>::iterator end = unique(nums.begin(), nums.end());
        int size = nums.size();
        int firstPositiveNumIndex = -1;
        int i = 0;
        int slotPositiveValue = 0;
        for (; i < end-nums.begin(); i++) {
            if (nums[i] > 0 && firstPositiveNumIndex == -1) firstPositiveNumIndex = i;
            if (firstPositiveNumIndex != -1) {
                slotPositiveValue = i - firstPositiveNumIndex + 1;
                if (slotPositiveValue!= nums[i]) break;
            }
        }

        if (firstPositiveNumIndex == -1) return 1;
        return i - firstPositiveNumIndex + 1;
    }
};

int main()
{
	vector<int> nums = {0,1,1,2,2};
	Solution sol;
	cout << sol.firstMissingPositive(nums);
}
