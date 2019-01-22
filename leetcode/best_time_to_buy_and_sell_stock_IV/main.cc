class Solution {
public:
    
    // dp[k][i] 第k次选择在第i次卖出的最大利润
    // dp[k][i] = std::min(dp[k-1][i], prices[i] - prices[j] + dp[k-1][j-1]);
    // prices[i] - prices[j] + dp[k-1][j-1] = prices[i] - (prices[j] - dp[k-1][j-1])
    // prices[j] - dp[k-1][j-1]最小即可
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()/2) {
            int sum = 0;
            for (int i = 1; i < prices.size(); i++) {
                sum += std::max(0, prices[i]-prices[i-1]);
            }
            return sum;
        }
        vector<int> dp(k+1);
        vector<int> min(k+1, prices[0]);
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 1; j <= k; j++) {
                min[j] = std::min(min[j], prices[i] - dp[j-1]);
                dp[j] = std::max(dp[j], prices[i] - min[j]);
            }
        }
        return dp[k];
    }
};
