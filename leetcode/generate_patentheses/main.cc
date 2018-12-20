class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> results;
        string result;
        int left = 0, right = 0;
        backtrack(results, result, left, right, n);
        return results;
    }
    
    void backtrack(vector<string>& results, string result, int left, int right, int n) {
        if (result.size() == 2*n) {
            results.push_back(result);
        }
        
        if (left < n) {
            backtrack(results, result + "(", left + 1, right, n);
        }
        
        if (right < left) {
            backtrack(results, result + ")", left, right+1, n);
        }
    }
};
