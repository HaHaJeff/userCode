class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }
        
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        
        for (int i = 0; i < dp.size(); i++) {
            dp[i][0] = matrix[i][0] - '0';
        }
        
        for (int j = 0; j < dp[0].size(); j++) {
            dp[0][j] = matrix[0][j] - '0';
        }
        
        int max = 0;
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 1; j < dp[0].size(); ++j) {
                if (matrix[i][j] == '1')
                    dp[i][j] += std::min(dp[i-1][j-1], std::min(dp[i][j-1], dp[i-1][j])) + 1;
            }
        }
        
        for (int i = 0; i < dp.size(); i++) {
            for (int j = 0; j < dp[0].size(); j++) {
                max = std::max(max, dp[i][j]);
            }
        }
        
        return max*max;
    }
};
