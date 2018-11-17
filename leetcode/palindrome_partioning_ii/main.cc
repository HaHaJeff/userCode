#include <string>
#include <vector>
#include <limits.h>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
	int minCut(string s) {
		std::map<int, int> cache;
		return recur(s, 0, 0, cache);
	}

	// cache: save the start from the start'th need minnest cut
	int recur(const std::string& s, int start, int cut, std::map<int, int>& cache) {
		if (start >= s.length()) { return cut - 1; }

		if (cache.find(start) != cache.end()) { return cache[start] + cut; }
		int min = INT_MAX;
		for (int i = start; i <= s.length(); ++i) {
			
			if (!isPalindrom(start, i, s)) {
				continue;
			}
			
			int ret = recur(s, i + 1, cut + 1, cache);
			min = std::min(ret, min);
		}
		cache[start] = min - cut;
		return min;
	}

	bool isPalindrom(int start, int end, const std::string &s) {
		while (start < end) {
			if (s[start++] != s[end--]) {
				return false;
			}
		}
		return true;
	}
};

int main()
{
	string s = "aab";
	Solution sol;

	int min = sol.minCut(s);

	std::cout << min << std::endl;
}
