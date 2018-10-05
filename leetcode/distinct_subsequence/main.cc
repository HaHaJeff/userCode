#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// 递归方法，超时!!!
//class Solution {
//public:
//	int numDistinct(string s, string t) {
//		return recur(0, s, 0, t);
//	}
//
//	int recur(int start1, const string& str1, int start2, const string& str2) {
//		if (start1 == str1.size() && start2 != str2.size()) {
//			return 0;
//		}
//
//		if (start2 == str2.size()) {
//			return 1;
//		}
//
//		int ret = 0;
//		std::pair<int, int> t(start1, start2);
//		if (dp.end() != dp.find(t)) return dp[t];
//		for (int i = start1; i < str1.size(); ++i) {
//
//			if (start2 < str2.size() && str1[i] == str2[start2]) {
//				ret += recur(i + 1, str1, start2 + 1, str2);
//				if (ret) dp.insert(std::pair<std::pair<int, int>, int>(t, ret));
//			}
//		}
//
//		return ret;
//	}
//
//private:
//	std::map<std::pair<int, int>, int> dp;
//};

//class Solution {
//public:
//	int numDistinct(string s, string t) {
//		dp = new int* [s.size()];
//		
//		for (int i = 0; i < s.size(); i++) dp[i] = new int[t.size()];
//
//		for (int i = 0; i < s.size(); i++) {
//			for (int j = 0; j < t.size(); j++) dp[i][j] = -1;
//		}
//
//		return recur(0, s, 0, t);
//	}
//
//	int recur(int start1, const string& str1, int start2, const string& str2) {
//		if (start1 == str1.size() && start2 != str2.size()) {
//			return 0;
//		}
//
//		if (start2 == str2.size()) {
//			return 1;
//		}
//
//		if (dp[start1][start2] != -1) return dp[start1][start2];
//
//		int ret = 0;
//
//		for (int i = start1; i < str1.size(); ++i) {
//			if (start2 < str2.size() && str1[i] == str2[start2]) {
//				ret += recur(i + 1, str1, start2 + 1, str2);
//			}
//		}
//		dp[start1][start2] = ret;
//		return ret;
//	}
//
//private:
//	int** dp;
//};

//DP 方法求解
// rabbbit
//r1111111
//a0111111
//b0012333
//b0001333
//i0000033
//t0000003

//if (a[i] == b[j]) dp[i][j] = dp[i][j-1] + dp[i-1][j-1]
//如果a[i]==b[j],则dp[i][j]由两部分组成，一部分有a[0,i-1]包含b[0,j]
//另外一部分由a[0,i-1]包含b[0,j-1]
class Solution {
public:
	int numDistinct(string s, string t) {
		dp = new int*[t.size()];

		for (int i = 0; i < t.size(); i++) dp[i] = new int[s.size()];

		for (int i = 0; i < t.size(); i++) {
			dp[i][0] = 0;
		}

		if (t[0] == s[0]) {
			dp[0][0] = 1;
		}
		else {
			dp[0][0] = 0;
		}

		for (int j = 1; j < s.size(); j++) {
			if (t[0] == s[j]) dp[0][j] = dp[0][j - 1] + 1;
			else dp[0][j] = dp[0][j - 1];
		}

		for (int i = 1; i < t.size(); i++) {
			for (int j = 1; j < s.size(); j++) {
				if (s[j] == t[i]) {
					dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = dp[i][j - 1];
				}
			}
		}

		return dp[t.size() - 1][s.size() - 1];
	}

private:
	int** dp;
};


int main()
{
	string str1 = "eee";
	string str2 = "eee";

	Solution sol;

	std::cout << sol.numDistinct(str1, str2) << std::endl;
}


//class Solution {
//public:
//	int numDistinct(string s, string t) {
//		return recur(0, s, 0, t);
//	}
//
//	int recur(int start1, const string& str1, int start2, const string& str2) {
//		if (start1 == str1.size() && start2 != str2.size()) {
//			return 0;
//		}
//
//		if (start2 == str2.size()) {
//			return 1;
//		}
//
//		std::pair< int, int> t(start1, start2);
//		if (dp.end() != dp.find(t)) return dp[t];
//		int ret = recur(start1 + 1, str1, start2, str2);;
//
//		if (start2 < str2.size() && str1[start1] == str2[start2]) {
//			ret += recur(start1 + 1, str1, start2 + 1, str2);
//			dp.insert(std::pair<std::pair<int, int>, int>(t, ret));
//		}
//
//
//		return ret;
//	}
//private:
//	std::map<std::pair<int, int>, int> dp;
//};
