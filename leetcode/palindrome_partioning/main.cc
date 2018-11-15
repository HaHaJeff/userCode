#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 使用回溯法
// 1. choose
// 2. explore
// 3. unchorse
class Solution {
public:
	vector<vector<string>> partition(string s) {
		vector<vector<string>> results;
		if (s.empty() || s.length() == 0) return results;

		vector<string> result;

		helper(s, 0, result, results);
		return results;
	}

	void helper(const string& s, int start, int end, vector<string>& result, vector<vector<string>>& results) {
		
		if (start > end) {
			results.push_back(result);
			return;
		}

		for (int len = 0; len < s.length() && start <= end && start+len < s.length(); len++) {
			if (!isPalindrome(start, start + len, s)) continue;

			result.push_back(s.substr(start, len+1));
			helper(s, start + len + 1, end, result, results);
			result.pop_back();
		}
	}

	void helper(const string& s, int start, vector<string>& result, vector<vector<string>>& results) {

		if (start >= s.length()) {
			results.push_back(result);
			return;
		}

		for (int i=start; i < s.length(); i++) {
			if (!isPalindrome(start, i, s)) continue;

			result.push_back(s.substr(start, i-start+1));
			helper(s, i+1, result, results);
			result.pop_back();
		}
	}

	bool isPalindrome(int start, int end, const string& s) {
		while (start <= end) {
			if (s[start] != s[end]) return false;
			++start;
			--end;
		}
		return true;
	}

};

int main()
{
	string s = "aab";
	Solution sol;

	vector<vector<string>> results = sol.partition(s);

	for (auto result : results) {
		for (auto str : result) {
			std::cout << str << "\t";
		}
		std::cout << std::endl;
	}
}
