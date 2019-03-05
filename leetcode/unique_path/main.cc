class Solution {
public:
    int uniquePaths(int m, int n) {
//        cache.resize(m+1);
//        for (auto& c : cache) c.resize(n+1, -1);
//        return dfs(1, 1, m, n);
        return dp(m, n);
    }
    
    
    int dp(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        dp[0][1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m][n];
        
    }
    
    int dfs(int i, int j, int m, int n) {
        if (i == m && j == n) {
            return 1;
        }
        if (i > m || j > n) {
            return 0;
        }
        if (cache[i][j] >= 0) return cache[i][j];
        int cnt = dfs(i+1, j, m, n) + dfs(i, j+1, m, n);
        cache[i][j] = cnt;
        return cnt;
    }
    
    vector<vector<int>> cache;
};
