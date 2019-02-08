class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<int> nums1 = {1, 2, 4, 8};
        vector<int> nums2 = {1, 2, 4, 8, 16, 32};
        vector<string> results;
        
        for (int i = 0; i <= num; i++) {
            vector<int> cmbNums1 = getDigit(nums1, i);
            vector<int> cmbNums2 = getDigit(nums2, num - i);
            for (auto& num1 : cmbNums1) {
                if (num1 >= 12) continue;
                for (auto& num2 : cmbNums2) {
                    if (num2 >= 60) continue;
                    results.push_back(to_string(num1)+":"+(num2<10?"0"+to_string(num2):to_string(num2)));
                }
            }
        }
        return results;
    }
    
    vector<int> getDigit(vector<int>& nums, int count) {
        vector<int> results;
        getDigitHelper(nums, count, 0, 0, results);
        return results;
    }
    
    void getDigitHelper(const vector<int>& nums, int count, int start, int sum, vector<int> & results) {
        if (count == 0) {
            results.push_back(sum);
            return;
        }
        
        for (int i = start; i < nums.size(); i++) {
            getDigitHelper(nums, count-1, i+1, sum+nums[i], results);
        }
    }
};
