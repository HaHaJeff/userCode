#include "leetcode.h"
//找出最长最小递增子序列
//在找的过程中如果发现当前值比子序列的末尾值还要小，说明该字符需要删除
class Solution {
public:
	string removeKdigits(string num, int k) {
		string stk = "";
		int top = 0;
		for (auto n : num) {

			while (top > 0 && n < stk.back() && k) {
				k--;
				stk.pop_back();
				top--;
			}

			if (n != '0' || top > 0) {
				top++;
				stk.push_back(n);
			}

		}

		while (stk.length() && k--) {
			stk.pop_back();
		}

		return stk.empty() ? "0" : stk;
	}
};
