class Solution1 {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> records;
        
        for (auto& num : nums) {
            records[num]++;
        }
        
        int half = nums.size()/2;
        for (auto& p : records) {
            if (p.second > half) {
                return p.first;
            }
        }
        return 0;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majorityIdx = 0;
        int cnt = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            nums[i] == nums[majorityIdx] ? cnt++ : cnt--;
            if (cnt == 0) {
                majorityIdx = i;
                cnt = 1;
            }
        }
        return nums[majorityIdx];
    }
};
