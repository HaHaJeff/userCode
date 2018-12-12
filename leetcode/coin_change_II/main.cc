#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	int change(int amount, vector<int>& coins) {
		dp.resize(coins.size());
		for (auto& item : dp) {
			item.resize(amount + 1, -1);
		}
		return dpOptSpace(amount, coins);
	}

	int recur(int target, int index, const vector<int>& coins) {
		int cnt = 0;
		if (index == coins.size()) {
			return target == 0 ? 1 : 0;
		}
		else {
			if (dp[index][target] != -1) { return dp[index][target]; }
			for (int i = 0; coins[index]*i <= target; i++) {
				cnt += recur(target - i*coins[index], index + 1, coins);
			}
			dp[index][target] = cnt;
		}
		return cnt;

	}

	int dpOrg(int target, const vector<int>& coins) {
		
		if (target < 0 || coins.empty()) {
			return 0;
		}

		for (int i = 0; i < coins.size(); i++) {
			dp[i][0] = 1;
		}

		for (int j = 0; coins[0] * j <= target; j++){
			dp[0][coins[0] * j] = 1;
		}

		int num = 0;
		for (int i = 1; i < coins.size(); i++) {
			for (int j = 1; j <= target; j++) {
				for (int k = 0; j - coins[i] * k >= 0; k++) {
					num += dp[i - 1][j - coins[i] * k];
				}
				dp[i][j] = num;
			}
		}

		return dp[coins.size()-1][target];
	}

	// dp[i][j] = dp[i-1][j] + dp[i-1][j-arr[i]] + dp[i-1][j-2*arr[i]] + ... + dp[i-1][j-k*arr[i]]
	// dp[i-1][j-arr[i]] + dp[i-1][j-2*arr[i]] + ... + dp[i-1][j-k*arr[i]] = dp[i][j-arr[i]]
	// dp[i][j] = dp[i-1][j] + dp[i][j-arr[i]
	int dpOptSpace(int target, const vector<int>& coins) {
		if (target == 0) return 1;
		if (target < 0 || coins.empty()) {
			return 0;
		}

		vector<int> dpSpace(target + 1, 0);

		for (int i = 0; coins[0] * i <= target; i++){
			dpSpace[coins[0]*i] = 1;
		}

		int num = 0;
		for (int i = 1; i < coins.size(); i++) {
			for (int j = 1; j <= target; j++) {
				dpSpace[j] += (j - coins[i]) >= 0 ? dpSpace[j - coins[i]] : 0;
			}
		}

		return dpSpace[target];
	}

	// dp[i][j] = dp[i-1][j] + dp[i-1][j-arr[i]] + dp[i-1][j-2*arr[i]] + ... + dp[i-1][j-k*arr[i]]
	// dp[i-1][j-arr[i]] + dp[i-1][j-2*arr[i]] + ... + dp[i-1][j-k*arr[i]] = dp[i][j-arr[i]]
	// dp[i][j] = dp[i-1][j] + dp[i][j-arr[i]
	int dpOpt(int target, const vector<int>& coins) {

		if (target < 0 || coins.empty()) {
			return 0;
		}

		for (int i = 0; i < coins.size(); i++) {
			dp[i][0] = 1;
		}

		for (int j = 0; coins[0] * j <= target; j++){
			dp[0][coins[0] * j] = 1;
		}

		int num = 0;
		for (int i = 1; i < coins.size(); i++) {
			for (int j = 1; j <= target; j++) {
				dp[i][j] = dp[i - 1][j];
				dp[i][j] += (j - coins[i]) >= 0 ? dp[i][j - coins[i]] : 0;
			}
		}

		return dp[coins.size() - 1][target];
	}
private:
	vector<vector<int>> dp;
};

int main()
{
	Solution sol;

	vector<int> coins = { 1, 2, 5 };
	int amount = 5;

	std::cout << sol.change(amount, coins) << std::endl;
}

