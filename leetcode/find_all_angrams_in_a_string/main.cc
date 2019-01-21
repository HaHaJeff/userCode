#include "leetcode.h"

class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		unordered_map<char, int> alpha;
		vector<int> results;
		for (auto& ch : p) {
			alpha[ch]++;
		}

		int left = 0, right = 0, size1 = s.size(), size2 = p.size();
		int cnt = 0;

		while (right < size1) {

			//说明right对应的值是p中有的，则此时窗口增大
			if (alpha.find(s[right]) != alpha.end() && alpha[s[right]] > 0) {
				alpha[s[right++]]--;
				cnt++;
			}
			else { // 说明right对应的值不是p中有的，或者已经出现过了
				if (alpha.find(s[right]) == alpha.end()) {
					for (int i = left; i < right; i++) {
						alpha[s[i]]++;
					}
					left = ++right;
					cnt = 0;
				}
				else {
					alpha[s[left++]]++;
					cnt--;
				}
			}

			if (cnt == size2) {
				results.push_back(left);
			}
		}
		return results;
	}

};
