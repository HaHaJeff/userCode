#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int nthUglyNumber(int n) {
		if (n == 1) return 1;

		int i = 1;
		int num = 0;

		int factor2{ 0 };
		int factor3{ 0 };
		int factor5{ 0 };
		
		vector<int> result(n, 0);
		result[0] = 1;

		while (i < n) {
			num = std::min(std::min(result[factor2] * 2, result[factor3] * 3), result[factor5] * 5);
			
			factor2 = (result[factor2] * 2 == num ? factor2 + 1 : factor2);
			factor3 = (result[factor3] * 3 == num ? factor3 + 1 : factor3);
			factor5 = (result[factor5] * 5 == num ? factor5 + 1 : factor5);

			result[i++] = num;
		}

		return result[n-1];
	}
};

int main()
{
	Solution sol;
	int n = 37;
	int num = sol.nthUglyNumber(n);
	std::cout << num << std::endl;
}
