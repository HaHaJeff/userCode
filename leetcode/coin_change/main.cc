// Input: coins = [1, 2, 5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
// 贪心法不行

class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {

		vector<int> dp(amount + 1);


		for (int i = 1; i <= amount; ++i) {
			int min = -1;
			for (auto coin : coins) {
				if (i >= coin && dp[i - coin] != -1) {
					int tmp = dp[i - coin] + 1;
					min = min < 0 ? tmp : (tmp < min ? tmp : min);
				}
			}
			dp[i] = min;
		}
		return dp[amount];
	}
};
