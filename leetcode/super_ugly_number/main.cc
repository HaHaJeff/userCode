#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> uglyIdx(primes.size(), 0), uglyNum(n, INT_MAX);
		uglyNum[0] = 1;
		
		for (int i = 1; i < n; i++) {
			int m = INT_MAX;
			for (int j = 0; j < primes.size(); j++) m = min(m, uglyNum[uglyIdx[j]] * primes[j]);
			for (int j = 0; j < primes.size(); j++) uglyIdx[j] += (m == primes[j] * uglyNum[uglyIdx[j]]);
			uglyNum[i] = m;
		}
		return uglyNum[n-1];
	}
};

int main()
{
	vector<int> primes = { 2, 7, 13, 19 };
	Solution sol;
	std::cout << sol.nthSuperUglyNumber(12, primes) << std::endl;
}
