#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
	int maxProfit(int g, vector<int>& prices) {
		int maxProfit;
		vector<vector<int>> dp(g+1, vector<int>(prices.size(), 0));

		// dp[k][i]表示：在第k次第ith天卖出的最大利润；
		// dp [k][i] = std::max(dp[k][i-1], prices[i] - prices[j] + dp[k-1][j-1]);
		for (int k = 1; k <= g; k++) {
			for (int i = 1; i < prices.size(); i++) {
				int min = prices[0];
				for (int j = 1; j <= i; j++) {
					min = std::min(prices[j] - dp[k - 1][j - 1], min);
				}
				dp[k][i] = std::max(dp[k][i - 1], prices[i] - min );
			}
		}

		for (int i = 1; i <= g; i++) {
			for (int j = 0; j < prices.size(); j++) {
				std::cout << dp[i][j] << " ";
			}
			std::cout << std::endl;
		}
		maxProfit = dp[g][prices.size() - 1];
		return maxProfit;
	}
};

int main() {
	std::vector<int> vec = { 3, 3, 5, 0, 0, 3, 1, 4 };
	Solution sol;
	std::cout << sol.maxProfit(2, vec) << std::endl;
}
