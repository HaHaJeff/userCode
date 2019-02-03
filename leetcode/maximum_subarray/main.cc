class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int tmpSum = 0;
        int maxSum = INT_MIN;
        
        for (auto& num : nums) {
            tmpSum = max(num, num+tmpSum);
            if (tmpSum > maxSum) {
                maxSum = tmpSum;
            }
        }
        
        return maxSum;
    }
};
