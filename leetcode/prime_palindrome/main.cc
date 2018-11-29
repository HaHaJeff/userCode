#include <iostream>
#include <algorithm>
class Solution {
public:
	int primePalindrome(int N) {
		for (int i = N;; i++) {
			if (isPrime(i) && isPalindrome(i)) {
				return i;
			}
		}
	}

	bool isPrime(int N) {
		if (N < 2 || N % 2 == 0) return N == 2;
		for (int d = 3; (d*d) < (N + 1); d+=2) {
			if (!(N%d))
				return false;
		}
		return true;
	}

	bool isPalindrome(int N) {
		int len = getLen(N);
		int end = len - 1;
		int start = 0;
		while (start < end) {
			int sIndex = getNumOfIndex(N, start);
			int eIndex = getNumOfIndex(N, end);
			if (sIndex != eIndex)
				return false;
			++start;
			--end;
		}
		return true;
	}

	int getNumOfIndex(int N, int index) {
		int len = getLen(N);
		if (index == 0) return N / pow(10, len - index - 1);
		int mod = pow(10, len - index);
		N %= mod;
		return N / pow(10, len - index - 1);
	}

	int getLen(int N) {
		int lens = 0;
		while (N) {
			++lens;
			N /= 10;
		}
		return lens;
	}
};

int main()
{
	Solution sol;
	std::cout << sol.primePalindrome(9989900) << std::endl;
}
