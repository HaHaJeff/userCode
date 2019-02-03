class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.empty()) return vector<int>();
        int candiate1 = nums[0];
        int candiate2 = nums[0];
        int cnt1 = 0;
        int cnt2 = 0;
        for (auto& num: nums) {
            if (num == candiate1) {
                cnt1++;
            } else if (num == candiate2) {
                cnt2++;
            } else if (cnt1 == 0) {
                candiate1 = num;
                cnt1++;
            } else if (cnt2 == 0) {
                candiate2 = num;
                cnt2++;
            } else {
                cnt1--;
                cnt2--;
            }
        }
        
        cnt1 = cnt2 = 0;
        for (auto& num : nums) {
            if (num == candiate1) cnt1++;
            else if(num == candiate2) cnt2++;
        }
        
        vector<int> ret;
        if (cnt1 > nums.size()/3) {
            ret.push_back(candiate1);
        }
        if (cnt2 > nums.size()/3) {
            ret.push_back(candiate2);
        }
        return ret;
    }
};
