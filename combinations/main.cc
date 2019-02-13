class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> results;
        vector<int> result;
        helper(results, result, 1, n, k);
        return# results;
    }
    
    void helper(vector<vector<int>>& results, vector<int>& result, int start, int n, int k) {
        if (k == 0) {
            results.push_back(result);
            return;
        }
        
        for (int i = start; i <= n; i++) {
            result.push_back(i);
            helper(results, result, i+1, n, k-1);
            result.pop_back();
        }
    }
};
