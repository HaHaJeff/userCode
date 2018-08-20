#include <iostream>
#include <vector>
#include <numeric>
#include <map>

using namespace std;

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		min_sum = std::numeric_limits<int>::max();
		x_bound = grid.size() - 1;
		y_bound = grid[0].size() - 1;

		//int sum = 0;
		//recur(0, 0, sum, grid);

		//return min_sum;

		vector<int> dp(y_bound + 1, 0);

		//dp[i][j] =  min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
		//dp[j] = min(dp[j], dp[j-1]) + grid[i][j];

		dp[0] = grid[0][0];
		for (int j = 1; j < x_bound + 1; j++) {
			dp[j] = dp[j - 1] + grid[0][j];	
		}

		dp[0] = 0;

		for (auto row : grid) {
			for (int j = 0; j < row.size(); j++) {
				if (j > 0) {
					dp[j] = (dp[j - 1] < dp[j] ? dp[j - 1] : dp[j]) + row[j];
				}
				else {
					dp[j] += row[j];
				}
			}
		}


		return dp[y_bound];
	}

private:
	void recur(int x, int y, int sum, vector<vector<int>>& grid) {
		if (x == x_bound && y == y_bound) {
			min_sum = sum + grid[x][y] < min_sum ? sum + grid[x][y] : min_sum;
			//min_sum = sum < min_sum ? sum : min_sum;
			return;
		}
		
		if (x > x_bound || y > y_bound) {
			return;
		}

		//pair<int, int> point{ x, y };
		recur(x + 1, y, sum + grid[x][y], grid);
		recur(x, y + 1, sum + grid[x][y], grid);
		//done.insert(pair<pair<int, int>, int>(point, min_sum - sum));
		
	}

	int x_bound;
	int y_bound;
	int min_sum;
	map<pair<int, int>, int> done;
};

int main() {
	vector<vector<int>> grid{
		{1, 3, 1},
		{1, 5, 1},
		{4, 2, 1}
	};


	Solution sol;
	int min = sol.minPathSum(grid);
	std::cout << min << std::endl;
}
