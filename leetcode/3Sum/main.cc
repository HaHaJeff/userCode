class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> results;
        
        std::sort(nums.begin(), nums.end());    
        int len = nums.size();
        
        for (int i = 0; i < len-2; i++) {
            
            int j = i+1;
            int k = len-1;
            while (j < k) {
                
                int sum = nums[i] + nums[j] + nums[k];
                if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                } else {
                    results.push_back({nums[i], nums[j], nums[k]});
                    while(j < k && nums[j] == nums[j+1]) j++;
                    while(j < k && nums[k] == nums[k-1]) k--;
                    j++;
                    k--;
                }
            }
            while(i < j && nums[i] == nums[i+1] ) i++;
        }
        
        return results;
    }
};
