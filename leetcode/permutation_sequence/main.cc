#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
	string getPermutation(int n, int k) {
		string str;
		for (int i = 1; i <= n; i++) {
			str.push_back(i + '0');
		}

		while (--k) {
			Iter begin = str.begin();
			Iter end = str.end();
			nextPermutation(begin, end);
		}
		return str;
	}

	using Iter = std::string::iterator;

	bool nextPermutation(Iter& first, Iter& last) {
		if (first == last) return false;
		Iter i = last;  // i指向第一个左边小于右边的位置
		if (--i == first) return false;

		while (true) {
			Iter i1 = i, i2 = last;
			//左边位置比右边小
			if (*--i < *i1) {
				//在i的右边找第一个比他大的
				while (!(*--i2 > *i))
					;

				std::iter_swap(i, i2);
				std::reverse(i1, last);
				return true;
			}
			if (i == first) {
				return false;
			}
		}
	}

	string getPer(int n, int k) {
		std::vector<char> cvec;
		for (int i = 1; i <= n; i++) {
			cvec.push_back(static_cast<char>(i + '0'));
		}

		std::vector<int> vec(n+1, 1);
		for (int i = 1; i <= n; i++) {
			vec[i] = vec[i - 1] * i;
		}
		string str;
		for (int i = 1; i <= n && k > 1; i++) {
			int index = ((k - 1) / vec[n - i]);
			str += cvec[index];
			cvec.erase(cvec.begin() + index);
			k -= index*vec[n - i];
		}

		for (auto ch : cvec) {
			str += ch;
		}
		return str;
	}

};
int main()
{
	Solution sol;
	vector<int> nums = {2, 2};
	string results = sol.getPer(2, 2);
	std::cout << results << std::endl;
}
