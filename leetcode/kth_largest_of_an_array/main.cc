class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>> q(nums.begin(), nums.end());
        for (int i = 0; i < k-1; i++) {
            q.pop();
        }
        return q.top();
    }
    int findKthLargest1(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, std::greater<int>> q;
        for (auto& num : nums) {
            q.push(num);
            if (q.size() > k) q.pop();
        }
        return q.top();
    }
};
