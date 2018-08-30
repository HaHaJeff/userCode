#include <iostream>
#include <string>

using namespace std;
/* 什么情况下满足条件
 * str1(0,i) == str2(0, i) && str1(i, end) == str2(i, end)
 * str1(0,i) == str2(size - i, end) && str1(i, end) == str2(0, size - i)
 */
class Solution {
public:
	bool isScramble(string s1, string s2) {

		if (s1.size() != s2.size()) return false;
		if (s1.empty() && s2.empty()) return true;

		bool ret = recur(s1, s2);
		return ret;
	}

	bool recur(string s1, string s2) {
		if (s1.size() == 1) {
			return s1 == s2;
		}

		if (s1 == s2) {
			return true;
		}

		//如果s1和s2包含的字符不同，则肯定不满足条件
		int tmp[26]{};
		for (int i = 0; i < s1.size(); i++) {
			tmp[s1[i] - 'a']++;
			tmp[s2[i] - 'a']--;
		}

		for (int i = 0; i < s2.size(); i++) {
			if (tmp[s1[i] - 'a'] != 0) return false;
		}

		if (s1.size() != s2.size()) return false;

		for (int i = 1; i < s1.size(); ++i) {
			if (recur(s1.substr(0, i), s2.substr(0, i)) && recur(s1.substr(i), s2.substr(i))) return true;
			if (recur(s1.substr(0, i), s2.substr(s1.size() - i)) && recur(s1.substr(i), s2.substr(0, s1.size() - i))) return true;
		}

		return false;
	}
};

int main()
{
	Solution sol;
	string str1{ "abcdefghijklmn" };
	string str2{ "efghijklmncadb" };
	std::cout << (sol.isScramble(str1, str2) == true ? "true" : "false") << std::endl;;
}
