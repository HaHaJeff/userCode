class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int sum = 0;
        vector<vector<int>> results;
        vector<int> result;
        backtrack(candidates, target, 0, sum, result, results);
        return results;
    }
    
    void backtrack(const vector<int>& candidates, int target, int begin, int sum, vector<int>& result, vector<vector<int>>& results) {
        if (target < sum) {
            return;
        }
        if (target == sum) {
            results.push_back(result);
            return;
        }
        for (int i = begin; i < candidates.size(); i++) {
            result.push_back(candidates[i]);
            backtrack(candidates, target, i, sum+candidates[i], result, results);
            result.pop_back();            
        }
    }
};
