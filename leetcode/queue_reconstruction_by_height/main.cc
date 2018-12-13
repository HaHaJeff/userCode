#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		auto comp = [](const pair<int, int>& p1, const pair<int, int>& p2){ return p1.first > p2.first || (p1.first == p2.first && p1.second <= p2.second); };
		sort(people.begin(), people.end(), comp);
		vector<pair<int, int>> res;
		for (auto p : people) {
			res.insert(res.begin() + p.second, p);
		}

		for (auto p : res) {
			std::cout << p.first << " " << p.second << std::endl;
		}
		return res;
	}
};

int main()
{
	Solution sol;

	vector<pair<int, int>> vec = { { 7, 0 }, { 4, 4 }, { 7, 1 }, { 5, 0 }, { 6, 1 }, { 5, 2 } };
	vector<pair<int, int>> res = sol.reconstructQueue(vec);

}
