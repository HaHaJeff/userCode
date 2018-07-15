#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits.h>
using namespace std;
class Solution1 {
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

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        std::set<int> s;

        for_each(nums.begin(), nums.end(), [&s](auto& i){s.insert(i);});
        int num = 1;

        for (num = 1; num < INT_MAX; num++) {
            if (s.find(num) == s.end()) {
                break;
            }
        }
        return num;
    }
};

int main()
{
	vector<int> nums = {0,1,1,2,2};
	Solution sol;
	cout << sol.firstMissingPositive(nums);
}
