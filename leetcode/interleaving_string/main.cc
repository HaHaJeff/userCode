#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int size1 = s1.length();
		int size2 = s2.length();

		if (size1 + size2 != s3.size()) return false;
		vector<vector<bool>> invalid(size1+1, vector<bool>(size2+1, false));
		return recur(s1, s2, s3, 0, 0, 0, invalid);
	}

	bool recur(string &s1, string &s2, string &s3, int i, int j, int k, vector<vector<bool>> &invalid) {
        if (k == s1.length() + s2.length()) return true;
		if (invalid[i][j]) return false;

		bool valid = (i < s1.length() && s1[i] == s3[k] && recur(s1, s2, s3, i + 1, j, k + 1, invalid)) ||
			(j < s2.length() && s2[j] == s3[k] && recur(s1, s2, s3, i, j + 1, k + 1, invalid));

		if (!valid) invalid[i][j] = true;

		return valid;
	}
};

int main()
{
	string s1 = "aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbbccca";

	Solution sol;
	std::cout << sol.isInterleave(s1, s2, s3) << std::endl;
}
