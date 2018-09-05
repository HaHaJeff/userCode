#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
	bool isNumber(string s) {

		int start = 0, end = s.size() - 1;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ' ') start++;
			else break;
		}

		for (int i = s.size() - 1; i >= 0; i--) {
			if (s[i] == ' ') end--;
			else break;
		}

		bool eSeen = false;
		bool numAfterE = false;
		bool numSeen = false;
		bool pointSeen = false;
		for (int i = start; i <= end; i++) {
			if (s[i] == '+' || s[i] == '-') {
				if (i != start && s[i - 1] != 'e') {
					return false;
				}
			}
			else if (s[i] >= '0' && s[i] <= '9') {
				numSeen = true;
				numAfterE = true;
			}
			else if (s[i] == 'e') { // only see 'e' once and 'e' can not be seen at first index or last index
				if (eSeen || !numSeen) {
					return false;
				}

				numAfterE = false;
				eSeen = true;
			}
			else if (s[i] == '.') {
				if (eSeen || pointSeen) {
					return false;
				}
				pointSeen = true;
			}
			else {
				return false;
			}
		}

		return numSeen && numAfterE;
	}
};


int main()
{
	std::string s = " -54.53061";
	Solution sol;
	std::cout << sol.isNumber(s) << std::endl;
}
