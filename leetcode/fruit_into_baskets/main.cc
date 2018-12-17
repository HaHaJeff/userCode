#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int x = []() { ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }();
class Solution {
public:
	int totalFruit(vector<int>& trees) {
		vector<int> baskets(2, -1);
		vector<int> indexStart(2, 0);
		int cnt = 0;
		int ret = 0;
		int last = 0;
		for (int i = 0; i < trees.size(); ++i) {

			auto iter = find(baskets.begin(), baskets.end(), trees[i]);
			//baskets have trees[i]
			if (iter != baskets.end()) {
				++cnt;
				if (last != *iter) {
					indexStart[iter - baskets.begin()] = i;
				}

			}
			else {
				int j = isFulled(baskets);
				if (j != -1) {
					indexStart[j] =  i;
					baskets[j] = trees[i];
					++cnt;
				}
				else {
					ret = max(cnt, ret);
					cnt = i - indexStart[1] + 1;
					indexStart[0] = indexStart[1] ;
					indexStart[1] = i;
					baskets[0] = baskets[1];
					baskets[1] = trees[i];
				}
			}
			last = trees[i];
		}
		ret = max(cnt, ret);
		return ret;
	}

	int isFulled(const vector<int>& baskets) {
		for (int i = 0; i < baskets.size(); ++i) {
			if (baskets[i] == -1) {
				return i;
			}
		}
		return -1;
	}
};

int main()
{
	Solution sol;
	vector<int> trees = {  2, 1, 6, 6, 4, 4, 6};

	std::cout << sol.totalFruit(trees) << std::endl;
}
