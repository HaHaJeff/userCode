class Solution {             
public:
    int arrayNesting(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int k = i, len = 0;
            while(nums[k] >= 0) {
                int origin = nums[k];
                nums[k] = -1;
                k = origin;
                len++;
            }
            res = max(len, res);
        }
        return res;
    }
};
