#include "leetcode.h"


class Solution {
public:
	int numDecodings(string s) {

		return numDP(s);
	}

	int numDecode(const string& s, int begin) {
		if (begin >= s.size()) return 1;

		int cnt = 0;
		int num1 = s[begin] - '0';
		if (num1 <= 26 && num1 >= 1) {
			cnt += numDecode(s, begin + 1);
		}

		if (begin < s.size() - 1) {
			int num2 = num1 * 10 + s[begin + 1] - '0';
			if (num1 != 0 && num2 <= 26 && num2 >= 1)
				cnt += numDecode(s, begin + 2);
		}

		return cnt;
	}

	// f(i) = f(i+1) + f(i+2)
	// f(i) = f(i-1)+f(i-2);
	int numDP(const string& s) {

		if (s.size() >= 1 && s[0] == '0') return 0;
		if (s.size() == 0) return 0;

		vector<int> dp(s.length() + 1);

		dp[0] = 1;
		dp[1] = 1;

		for (int i = 2; i <= s.size(); i++) {
			if (s[i - 1] > '0' && s[i - 1] <= '9') dp[i] += dp[i - 1];
			if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')) dp[i] += dp[i - 2];
		}

		return dp[s.size()];
	}

};
//
//int main()
//{
//	Solution sol;
//
//	string s = "2222";
//	
//	std::cout << sol.numDecodings(s) << std::endl;
//}
