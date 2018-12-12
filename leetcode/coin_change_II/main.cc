#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	int change(int amount, vector<int>& coins) {
		dp.resize(amount + 1);
		for (auto& item : dp) {
			item.resize(coins.size(), -1);
		}
		return recur(amount, 0, coins);
	}

	int recur(int target, int index, const vector<int>& coins) {
		int cnt = 0;
		if (index == coins.size()) {
			return target == 0 ? 1 : 0;
		}
		else {
			if (dp[target][index] != -1) { return dp[target][index]; }
			for (int i = 0; coins[index]*i <= target; i++) {
				cnt += recur(target - i*coins[index], index + 1, coins);
			}
			dp[target][index] = cnt;
		}
		return cnt;

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
