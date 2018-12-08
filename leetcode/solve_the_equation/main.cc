#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

class Solution {
public:
	string solveEquation(string equation) {
		infinite = "Infinite solutions";
		nosolution = "No solution";

		int i = 0;
		int para = 0, coeff = 0;
		int sign = 0;
		int temp = 0;
		int flag = 1;

		while (i < equation.size()) {
			sign = 1;
			temp = 0;

			//计算等式右边
			if (equation[i] == '=') {
				flag = -1;
				i++;
			}

			if (equation[i] == '+') {
				sign = 1;
				i++;
			}

			if (equation[i] == '-') {
				sign = -1;
				i++;
			}

			if (isdigit(equation[i])) {
				// 计算数值部分大小
				while (i < equation.size() && isdigit(equation[i])) {
					temp = temp * 10 + equation[i] - '0';
					i++;
				}

				if (i < equation.size() && equation[i] == 'x') {
					coeff += flag*sign*temp;
					i++;
				}
				else {
					para += flag*sign*temp;
				}
			}
			else {
				coeff += flag*sign;
				i++;
			}
		}

		string res;

		if (para == 0 && coeff == 0) {
			res = infinite;
		}
		else if(coeff == 0) {
			res = nosolution;
		}
		else {
			res = "x=" + to_string(para / coeff*-1);
		}

		return res;
		
	}

private:
	string infinite;
	string nosolution;

};
int main()
{
	Solution sol;

	std::cout << sol.solveEquation("x+5-3+x=6+x-2") << std::endl;
}
