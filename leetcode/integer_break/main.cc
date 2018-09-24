#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int integerBreak(int n) {
		vector<int> dp(n + 1);

		dp[1] = 1;
		dp[2] = 1;
		dp[3] = 2;
		dp[4] = 4;

		for (int i = 5; i <= n; i++) {
			int max = 0;
			for (int j = 1; j < i; j++) {
				int max1 = std::max(dp[i-j]*dp[j], dp[i-j]*j);
				int max2 = std::max((i-j)*dp[j], (i-j)*j);
				max = std::max(max, std::max(max1, max2));
			}
			dp[i] = max;
		}

		return dp[n];
	}
};

int main()
{
	Solution sol;

	int n = 10;
	std::cout << sol.integerBreak(n) << std::endl;
}
