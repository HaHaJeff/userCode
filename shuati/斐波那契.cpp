#include "header.h"

// 斐波那契梳理
// 思路：采用迭代法求解，cur = prev + pprev
class Solution {
public:
	int Fibonacci(int n) {
		if (n == 0) return 0;
		if (n <= 2) return 1;
		int prev = 1, pprev = 1, ret = 0;
		for (int i = 3; i <= n; i++) {
			ret = prev + pprev;
			pprev = prev;
			prev = ret;
		}
		return ret;
	}
};