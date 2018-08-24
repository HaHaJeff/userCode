#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

//  A B C  word2
//B 1 1 2
//C 2 2 1
//D 3 3 2
//word1
//对于AB与BC来说，将AB变为BC的方式 要么删除B，要么在AB添加C，要么将B换成C
class Solution {
public:
	int minDistance(string word1, string word2) {
		int size1 = word1.length(), size2 = word2.length();
		vector<vector<int> > dp(size1, vector<int>(size2, 0));
		dp[0][0] = (word1[0] == word2[0] ? 0 : 1);
		bool ocured = false;

		for (int i = 1; i < size1; ++i) {
			if (word1[i] == word2[0] && !ocured)  {
				dp[i][0] = dp[i - 1][0];
				ocured = true;
			}
			else dp[i][0] = dp[i-1][0] + 1;
		}

		ocured = false;

		for (int i = 1; i < size2; ++i) {
			if (word1[0] == word2[i] && !false) {
				dp[0][i] = dp[0][i - 1];
				ocured = true;
			}
			else dp[0][i] = dp[0][i-1] + 1;
		}

		for (int i = 1; i < size1; ++i) {
			for (int j = 1; j < size2; ++j) {
				if (word1[i] == word2[j]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = std::min(std::min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1), dp[i - 1][j] + 1);
				}
			}
		}

		for (auto item : dp) {
			for (auto i : item) {
				std::cout << i << "\t";
			}
			std::cout << "\n";
		}

		return dp[size1 - 1][size2 - 1];
	}
};

int main()
{
	string word1 = "a";
	string word2 = "ab";
	Solution sol;
	std::cout << sol.minDistance(word1, word2) << std::endl;
}
