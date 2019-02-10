class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> results;
        vector<int> result;
        helper(results, result, 1, k, n);
        return results;
    }
    
    void helper(vector<vector<int>>& results, vector<int>& result, int pos, int k, int n) {
        if (n == 0 && result.size() == k) {
            results.push_back(result);
            return;
        }
        
        for (int i = pos; i <= 9 && n > 0 && result.size() < k; i++) {
            result.push_back(i);
            helper(results, result, i+1, k, n-i);
            result.pop_back();
        }
    }
};
