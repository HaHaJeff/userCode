#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
class Solution {
public:
	int numSquares(int n) {
	
		return dp(n);
	}

	int dp(int n) {
		static std::vector<int> dp(1, 0);
		for (int i = 1; i <= n; i++) {
			dp[i] = i;
			for (int j = 1; j*j <= i; j++)  {
				dp[i] = std::min(dp[i], dp[i - j*j] + 1);
			}
		}
		return dp[n];
	}

	int recur(int n) {
		if (n == 0) {
			return 0;
		}

		return recur(n - pow(static_cast<int>(sqrt(n)), 2)) + 1;
	}

	int recur1(int n) {

		if (n == 0) {
			return 0;
		}

		int min = INT_MAX;
		if (dp_.find(n) != dp_.end()) return dp_[n];
		for (int i = 1; i*i <= n; i++) {

			int ret = recur1(n - i*i) + 1;
			min = std::min(min, ret);

		}
		dp_[n] = min;
		return min;
	}
private:
	std::map<int, int> dp_;
};

int main()
{
	int n = 48;

	Solution sol;
	std::cout << sol.numSquares(n) << std::endl;
}
