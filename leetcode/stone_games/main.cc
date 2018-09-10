#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//如何保证必胜，因为每个人在选择的时候都会选择最大的
//dp[i][j]表示i-j之间两方选择的值的和的差
//如果选择p[i]：则dp[i][j] = p[i] - dp[i+1][j]  dp[i+1][j]表示另外一个人上一轮的选择
//否则：则dp[i][j] = p[j] - dp[i][j-1]         dp[i][j-1]表示另外一个人上一轮的选择
class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		if (piles.empty()) return true;
		int size = piles.size();
		vector<vector<int> > dp(size, vector<int>(size, 0));

		for (int i = 0; i < size; ++i) {
			dp[i][i] = piles[i];
		}

		for (int len = 1; len < size; ++len) {
			for (int i = 0; i < size - len; ++i) {
				dp[i][i + len] = std::max(piles[i] - dp[i + 1][i + len], piles[i + len] - dp[i][i + len - 1]);
			}
		}

		return dp[0][size - 1] > 0;
	}
};
