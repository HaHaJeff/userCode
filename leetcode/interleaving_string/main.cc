#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int size1 = s1.length();
		int size2 = s2.length();

		if (size1 + size2 != s3.size()) return false;
		vector<vector<bool>> invalid(size1+1, vector<bool>(size2+1, false));
		return recur(s1, s2, s3, 0, 0, 0, invalid);
	}

	bool recur(string &s1, string &s2, string &s3, int i, int j, int k, vector<vector<bool>> &invalid) {
        if (k == s1.length() + s2.length()) return true;
		if (invalid[i][j]) return false;

		bool valid = (i < s1.length() && s1[i] == s3[k] && recur(s1, s2, s3, i + 1, j, k + 1, invalid)) ||
			(j < s2.length() && s2[j] == s3[k] && recur(s1, s2, s3, i, j + 1, k + 1, invalid));

		if (!valid) invalid[i][j] = true;

		return valid;
	}
    	//dp[i][j]表示 s1 i位置以及 s2 j位置是否满足 s3 i+j
	//如果s3满足s1与s2 interleaving，那么s3[last] == s1[last] or s2[last]递推回去
	bool dp(string s1, string s2, string s3) {
		int size1 = s1.size();
		int size2 = s2.size();
		int size3 = s3.size();
		vector<vector<bool>> dp(size1+1, vector<bool>(size2+1, false));

		for (int i = 1; i < size1 + 1; i++) {
			dp[i][0] = s1.substr(0, i) == s3.substr(0, i) ? true : false;
		}

		for (int j = 1; j < size2 + 1; j++) {
			dp[0][j] = s2.substr(0, j) == s3.substr(0, j) ? true : false;
		}

		for (int i = 1; i < size1 + 1; i++) {
			for (int j = 1; j < size2 + 1; j++) {
				dp[i][j] = (s1[i - 1] == s3[i - 1 + j] ? dp[i - 1][j] : (s2[j - 1] == s3[i + j - 1] ? dp[i][j - 1] : false));
			}
		}

		return dp[size1][size2];
	}
};

int main()
{
	string s1 = "aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbbccca";

	Solution sol;
	std::cout << sol.isInterleave(s1, s2, s3) << std::endl;
}
