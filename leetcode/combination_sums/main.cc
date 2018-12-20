class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int sum = 0;
        vector<vector<int>> results;
        vector<int> result;
        std::sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, result, results);
        return results;
    }
    
    void backtrack(const vector<int>& candidates, int target, int begin, vector<int>& result, vector<vector<int>>& results) {
        if (target == 0) {
            results.push_back(result);
            return;
        }
        for (int i = begin; i < candidates.size()&&target >= candidates[i]; i++) {
            result.push_back(candidates[i]);
            backtrack(candidates, target-candidates[i], i,result, results);
            result.pop_back();            
        }
    }
};
