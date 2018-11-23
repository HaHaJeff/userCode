#include <iostream>
class Solution {
public:
	int numTrees(int n) {
		return recur(1, n, true);
	}

	int recur(int start, int end, bool bLeft) {

		if (start >= end) return 1;

		int left = 0;
		int right = 0;
		int sum = 0;
		for (int i = start; i <= end; i++) {
			left = recur(start, i - 1, true);
			right = recur(i + 1, end, false);
			sum += (left*right);
		}

		return sum;
	}
};
