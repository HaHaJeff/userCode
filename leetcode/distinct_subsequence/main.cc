#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int numDistinct(string s, string t) {
		return recur(0, s, 0, t);
	}

	int recur(int start1, const string& str1, int start2, const string& str2) {
		if (start1 == str1.size() && start2 != str2.size()) {
			return 0;
		}

		if (start2 == str2.size()) {
			return 1;
		}

		int ret = 0;

		for (int i = start1; i < str1.size(); ++i) {
			if (start2 < str2.size() && str1[i] == str2[start2]) {
				ret += recur(i+1, str1, start2+1, str2);
			}
		}

		return ret;
	}
};

//int main()
//{
//	string str1 = "babgbag";
//	string str2 = "bag";
//
//	Solution sol;
//
//	std::cout << sol.numDistinct(str1, str2) << std::endl;
//}
