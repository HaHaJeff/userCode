class Solution {
public:
    vector<int> intersect1(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        vector<int> result;
        for (auto& num1 : nums1) {
            m[num1]++;
        }
        for (auto& num2 : nums2) {
            if (m.find(num2) != m.end() && --m[num2] >= 0) result.push_back(num2);
        }
        return result;
    }
    
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        while(i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) i++;
            else if (nums1[i] > nums2[j]) j++;
            else {
                result.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        return result;
    }
    
};
s
