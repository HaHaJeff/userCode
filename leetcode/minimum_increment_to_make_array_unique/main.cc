#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int minIncrementForUnique(vector<int>& A) {
		int need = 0, res = 0;
		// 3 2 1 2 1 7
		// 1 1 2 2 3 7
		// 1 2 3 4 5 6
		//   n n n n n 
		// n表示最小化unqiue array需要出现的数字，如果need比num小的话说明不需要变化
		// n如何更新：需要上一个n和上一个num的最大值+1即可
 		sort(A.begin(), A.end());
		
		for (auto a : A) {
			res += max(need - a, 0);
			need = max(need, a) + 1;
		}

		return res;
	}
};

int main()
{
	vector<int> nums = { 3, 2, 1, 2, 1, 7 };
	Solution sol;
	std::cout << sol.minIncrementForUnique(nums) << std::endl;
}
