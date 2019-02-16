#include "header.h"

// 青蛙跳台阶问题
// 思路：考虑目前处于第n个台阶，如何跳上第n个台阶呢？有两种方式：
// 1. 从n-1跳一个台阶 
// 2. 从n-2条两个台阶
// 3. f(n) = f(n-1) + f(n-2)
class Solution {
public:
	int jumpFloor(int number)
	{
		int number1 = 1;
		int number2 = 2;
		int numbern;
		if (number == 1) return number1;
		if (number == 2) return number2;

		for (int i = 3; i <= number; i++) {
			numbern = number1 + number2;
			number1 = number2;
			number2 = numbern;
		}
		return numbern;
	}
};