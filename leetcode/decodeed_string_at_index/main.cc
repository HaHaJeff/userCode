#include "leetcode.h"

class Solution {
public:
	//string decodeAtIndex(string S, int K) {
	//	string ret;
	//	string tmp;

	//	for (int i = 0; i < S.length() && tmp.size() <= K; i++) {
	//		if (isdigit(S[i])) {
	//			int num = S[i] - '0';
	//			for (int j = 1; j < num; j++) {
	//				tmp += tmp;
	//			}
	//		}
	//		else {
	//			tmp += S[i];
	//		}

	//	}
	//	ret = tmp[K - 1];
	//	return ret;
	//}
	// a2b3c4
	// 当index指向3时，前面的字符长度为3，当index指向4时，前面的字符长度10
	string decodeAtIndex(string S, int K) {

		int N = 0;
		int i = 0;
		for (i = 0; N < K; i++) {
			N = isdigit(S[i]) ? N * (S[i] - '0') : N + 1;
		}

		while (i--) {
			if (isdigit(S[i])) {
				N /= (S[i] - '0');
				K %= N;
			}
			else if (K%N-- == 0){
				return string(1, S[i]);
			}
		}
	}
};
