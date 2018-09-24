#include <iostream>
#include <vector>

using namespace std;

// 0   0000   0
// 1   0001   1
// 2   0010   1
// 3   0011   2
// 4   0100   1
// 5   0101   2
// 6   0110   2
// 7   0111   3
// 8   1000   1

// 如果最后一位为1，则dp[i] = dp[i>>1] + 1;
// 如果最后一位为0，则dp[i] = dp[i>>1];
class Solution {
public:
	vector<int> countBits(int num) {

		vector<int> dp(num + 1);
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= num; i++) {
			dp[i] = dp[i >> 1] + (i & 1);
		}
		return dp;
	}
};

int main()
{
	int num = 9;

	Solution sol;
	auto results = sol.countBits(num);

	int n = 0;
	for (auto item : results) {
		std::cout << "index: " << n++ << "\tvalue: " << item << "\n";
	}

}
