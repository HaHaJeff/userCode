#include <iostream>
#include <vector>

class Solution {
public:
	int numSquares(int n) {
		return recur(n);
	}

	int recur(int n) {
		if (n == 0) {
			return 0;
		}

		return recur(n - pow(static_cast<int>(sqrt(n)), 2)) + 1;
	}
};

int main()
{
	int n = 19;

	Solution sol;
	std::cout << sol.numSquares(n) << std::endl;
}
