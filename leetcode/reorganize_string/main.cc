#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
	string reorganizeString(string S) {
		map<char, int> charCount;

		for (auto ch : S) {
			charCount[ch]++;
		}

		vector<pair<int, char>> charVec;

		for (auto p : charCount) {
			if (p.second > (S.size() + 1) / 2) return "";
			charVec.push_back(pair<int, char>(p.second, p.first));
		}

		sort(charVec.rbegin(), charVec.rend());
		string strSorted;
		for (auto p : charVec) {
			strSorted += string(p.first, p.second);
		}

		string ret;
		for (int i = 0, j = (S.size() - 1) / 2 + 1; i <= (S.size() - 1) / 2; ++i, ++j) {
			ret += strSorted[i];
			if (j < S.size()) ret += strSorted[j];
		}
		return ret;
	}
};


int main()
{
	string s = "aab";
	Solution sol;
	std::cout << sol.reorganizeString(s) << std::endl;
}

