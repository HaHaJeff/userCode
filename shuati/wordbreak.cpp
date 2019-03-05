#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution1 {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		if (s == "") return true;
		for (int i = 1; i <= s.size(); i++) {
			if (dict.count(s.substr(0, i)) && wordBreak(s.substr(i), dict)) {
				std::cout << s.substr(i) << std::endl;
				return true;
			}
		}
		return false;
	}
};

int main()
{
	unordered_set<string> dict = { "aaa", "aaaa" };
	Solution1 sol;
	string str = "aaaaaaa";
	std::cout << sol.wordBreak(str, dict) << std::endl;

}
