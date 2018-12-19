#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	// 1. 保证S的字符与word中包含的一样
	// 2. 保证两个字符串间除了相同的子集外，S中要么当前的字符和word中不一样且 当前的字符包含重复3次以上，要么返回fasle
	int expressiveWords(string S, vector<string>& words) {
		int i = 0, j = 0, ret = 0;

		for (auto word : words) {
			if (word.size() > S.size()) continue;
			for (i = 0, j = 0; i < S.size(); i++) {
				if (word[j] == S[i]) j++;
				else if (i >= 2 && S[i - 2] == S[i - 1] && S[i - 2] == S[i]) i;
				else if (i >= 1 && i < S.size() - 1 &&  S[i - 1] == S[i] && S[i - 1] == S[i + 1]) i++;
				else if (i < S.size() - 2 && S[i] == S[i + 1] && S[i] == S[i + 2]) i += 2;
				else break;
			}
			if (i == S.size() && j == word.size()) ret++;
		}
		return ret;
	}
};

int main()
{
	string S = "dddiiiinnssssssoooo";
	vector<string> words = { "dinnssoo", "ddinso", "ddiinnso", "ddiinnssoo", "ddiinso", "dinsoo", "ddiinsso", "dinssoo", "dinso" };

	Solution sol;
	std::cout << sol.expressiveWords(S, words) << std::endl;
}

