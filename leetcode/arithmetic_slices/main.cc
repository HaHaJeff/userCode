class Solution {
public:
    // dp[i]表示以A[i]结尾的满足条件的个数
    int numberOfArithmeticSlices(vector<int>& A) {
        vector<int> dp(A.size(), 0);
        if (A.size() < 3) return 0;
        if (A[2]-A[1] == A[1]-A[0]) dp[2] = 1;
        int result = dp[2];
        
        for (int i = 3; i < A.size(); i++) {
            if (A[i]-A[i-1] == A[i-1]-A[i-2]) {
                // +1表示dp[i-1]中的A[i-2]A[i-1]A[i]也是的
                dp[i] = dp[i-1]+1;
            }
            result += dp[i];
        }
        return result;
    }
};
