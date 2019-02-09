class Solution {
public:
    int countArrangement(int N) {
        vector<int> nums(N);
        for (int i = 1; i<=N; i++) nums[i-1] = i;
        return helper(nums, 0);
    }
    
    int helper(vector<int>& nums, int start) {
        if (start == nums.size()) {
            return 1;
        }
        int cnt = 0;
        for (int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);
            if (nums[i] % (i+1) == 0 || (i+1) % nums[i] == 0) {
                cnt += helper(nums, start+1);   
            }
            swap(nums[i], nums[start]);
        }
        return cnt;
    }
};
