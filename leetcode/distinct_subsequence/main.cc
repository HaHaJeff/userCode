#include <iostream>
#include <string>
#include <vector>
#include <map>

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

// runtime: 12ms 7.64%
class Solution {
public:
	int numDistinct(string s, string t) {
		dp = new int* [s.size()];
		
		for (int i = 0; i < s.size(); i++) dp[i] = new int[t.size()];

		for (int i = 0; i < s.size(); i++) {
			for (int j = 0; j < t.size(); j++) dp[i][j] = -1;
		}

		return recur(0, s, 0, t);
	}

	int recur(int start1, const string& str1, int start2, const string& str2) {
		if (start1 == str1.size() && start2 != str2.size()) {
			return 0;
		}

		if (start2 == str2.size()) {
			return 1;
		}

		if (dp[start1][start2] != -1) return dp[start1][start2];

		int ret = 0;

		for (int i = start1; i < str1.size(); ++i) {
			if (start2 < str2.size() && str1[i] == str2[start2]) {
				ret += recur(i + 1, str1, start2 + 1, str2);
			}
		}
		dp[start1][start2] = ret;
		return ret;
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
