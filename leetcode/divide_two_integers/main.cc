class Solution {
public:
	int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
		if (dividend == 0) return 0;
		bool flag = true;
		if ((dividend < 0 && divisor < 0) || (dividend > 0 && divisor > 0)) { flag = false; }
		unsigned first = dividend == INT_MIN ? (unsigned)INT_MAX + 1 : abs(dividend);
		unsigned second = divisor == INT_MIN ? (unsigned)INT_MAX + 1 : abs(divisor);
		
		unsigned cnt = 0;

		while (first >= second) {
			int i = 0;
			while (first >= (second << i)) {
				i++;
				if (i != 0 && (second << i) < (second << (i - 1))) break;
			}
			first -= second << (i - 1);
			cnt += 1 << (i-1);
		}

		return !flag ? (cnt) : (0 - cnt);
	}
};
