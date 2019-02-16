#include "header.h"

// ������̨������
// ˼·������Ŀǰ���ڵ�n��̨�ף�������ϵ�n��̨���أ������ַ�ʽ��
// 1. ��n-1��һ��̨�� 
// 2. ��n-2������̨��
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