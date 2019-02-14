class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        //unordered_map<int, int> hash;
        vector<int> hash(20001);
        for (auto& num : nums) {
            hash[num+10000]++;
        }
        
        int res = 0, flag = 0;
        
        for (int i = 1; i < 20001;) {
            if (hash[i] > 0 && flag == 0) {
                res += i - 10000;
                flag = 1;
                --hash[i];
            } else if (hash[i] > 0 && flag == 1) {
                flag = 0;
                --hash[i];
            } else {
                ++i;
            }
        }
        return res;
    }
};
