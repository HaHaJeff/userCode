#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
class Solution {
public:
	bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
		auto dis = [](vector<int>& p1, vector<int>& p2) { return (p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]); };
		unordered_set<int> set = { dis(p1, p2), dis(p1, p3), dis(p1, p4), dis(p2, p3), dis(p2, p4), dis(p3, p4) };
		return !set.count(0) && set.size() == 2;
	}
};
int main()
{
	Solution sol;
	vector<int> p1 = { 0, 0 }, p2 = { 1, 1 }, p3 = { 1, 0 }, p4 = { 0, 1 };
	std::cout << sol.validSquare(p1, p2, p3, p4) << std::endl;
}
