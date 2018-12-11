#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int numMatchingSubseq(string S, vector<string>& words) {
		vector<vector<int>> alpha(26);
		for (int i = 0; i < S.size(); ++i) alpha[S[i] - 'a'].push_back(i);
		int res = 0;
		for (const auto& word : words) {
			int index = -1;
			bool found = true;

			for (auto ch : word) {
				auto it = upper_bound(alpha[ch - 'a'].begin(), alpha[ch - 'a'].end(), index);
				if (it == alpha[ch - 'a'].end()) {
					found = false;
					break;
				}
				else {
					index = *it;
				}
			}
			if (found) ++res;
		}
		return res;
	}
};

//int main()
//{
//	Solution sol;
//	vector<string> words = { "a", "bb", "acd", "ace" };
//	std::cout << sol.numMatchingSubseq("abcde", words) << std::endl;
//}
