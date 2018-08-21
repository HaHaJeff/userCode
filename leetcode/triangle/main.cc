#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {


		//dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + triangles[i][j]
		for (int i = 1; i < triangle.size(); i++) {
			for (int j = 0; j < i + 1; j++) {
				if (j == 0) {
					triangle[i][j] += triangle[i - 1][j];
				}
				else if (j == i) {
					triangle[i][j] += triangle[i - 1][j - 1];
				}
				else {
					triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
				}
			}
		}

		int min = std::numeric_limits<int>::max();

		for (auto item : triangle[triangle.size()-1]) {
			min = (min < item ? min : item);
		}
		
		return min;
	}
};

int main()
{
	vector<vector<int>> triangle{ { 2 }, { 3, 4 }, { 6, 5, 7 }, {4,1,8,3} };

	Solution sol;
	std::cout << sol.minimumTotal(triangle) << std::endl;
}
