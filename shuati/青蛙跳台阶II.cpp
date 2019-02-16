#include "header.h"

// 青蛙跳台阶II
// 思路：f(n) = f(n-1) + f(n-2) + ... + f(0)
// f(n-1) = f(n-2) + f(n-3) + ... + f(0)
// f(n) = f(n-1) + f(n-1)
// f(n) = 2*f(n-1)
class Solution {
public:
	int jumpFloorII(int number) {
		return pow(2, number - 1);
	}
};