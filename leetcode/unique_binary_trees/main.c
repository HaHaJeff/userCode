#include <iostream>
#include <map>
#include <vector>
class Solution {
public:
	int numTrees(int n) {
		dp.resize(n+1);
		for (int i = 0; i < n+1; ++i) {
			dp[i].resize(n+1);
		}
		return recur(1, n);
	}

	int recur(int start, int end) {

		if (start > end) return 1;

		int left = 0;
		int right = 0;

		if (dp[start][end] != 0) return dp[start][end];

		for (int i = start; i <= end; i++) {

			left = recur(start, i - 1);
			right = recur(i + 1, end);
			dp[start][end] += (left*right);
		}
		return dp[start][end];
	}

private:
	std::vector<std::vector<int>> dp;
};


int main()
{
	Solution sol;
	std::cout << sol.numTrees(3) << std::endl;
}
