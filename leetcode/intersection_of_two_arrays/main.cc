class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        std::set<int> s(nums1.begin(), nums1.end());  
        for (auto& num2 : nums2) {
            if (s.count(num2)) {
                result.push_back(num2);  
                s.erase(num2);
            }
        }
        return result;
    }
};
