#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

static int x = []() { ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
class Solution {
public:
	vector<int> advantageCount(vector<int>& A, vector<int>& B) {

		vector<int> ret;
		multiset<int> s(A.begin(), A.end());
		for (auto n : B) {
			auto iter = s.upper_bound(n);
			if (iter == s.end()) {
				ret.push_back(*s.begin());
				s.erase(s.begin());
				continue;
			}
			ret.push_back(*iter);
			s.erase(iter);
		}

		return ret;
	}
};

int main()
{
	Solution sol;
	vector<int> A = { 2, 0, 4, 1, 2 }, B = { 1, 3, 0, 0, 2 };
	vector<int> ret = sol.advantageCount(A, B);

	for (auto i : ret) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
