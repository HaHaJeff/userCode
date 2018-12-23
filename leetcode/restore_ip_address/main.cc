#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		int a = 0, b = 0, c = 0, d = 0;
		vector<string> results;
		for (a = 1; a < 4 && a <= s.length()-3; ++a) {
			string A = s.substr(0, a);
			for (b = 1; b < 4 && a + b <= s.length() - 2; ++b) {
				string B = s.substr(0+a, b);
				for (c = 1; c < 4 && a + b + c <= s.length() - 1; ++c) {
					string C = s.substr(0 + a + b, c);
					for (d = 1; d < 3 && a + b + c + d <= s.length(); ++d) {
						string D = s.substr(0 + a + b + c, d);
						if (stoi(A) <= 255 && stoi(B) <= 255 && stoi(C) <= 255 && stoi(D) <= 255 && A.size() + B.size() + C.size() + D.size() == s.length()) {
							results.push_back(A + "." + B + "." + C + "." + D);
						}
					}
				}
			}
		}
		return results;
	}
};

