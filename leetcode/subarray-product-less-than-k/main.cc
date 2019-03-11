// 在滑动窗口增加一个数，相当于在原窗口中：
// 1 2 3     add 4
// 4， 3 4， 2 3 4，1 2 3 4
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) return 0;
        return slideWindow(nums, k);
    }
    
    int slideWindow(vector<int>& nums, int k) {
        int prod = 1;
        int ans = 0;
        for (int l = 0, r = 0; r < nums.size(); r++) {
            prod *= nums[r];
            while (l <= r && prod >= k) {
                prod /= nums[l++];
            }
            ans += r - l + 1;
        }
        return ans;
    }
};
