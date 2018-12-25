#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	string getPermutation(int n, int k) {
		string str;
		for (int i = 1; i <= n; i++) {
			str.push_back(i + '0');
		}

		while (--k) {
			std::next_permutation(str.begin(), str.end());
		}
		return str;
	}

};

int main()
{
	Solution sol;
	vector<int> nums = { 1, 2, 3 };
	string results = sol.getPermutation(3, 5);
	std::cout << results << std::endl;
}
