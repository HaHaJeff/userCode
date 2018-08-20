class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		x_bound = obstacleGrid.size() - 1;
		y_bound = obstacleGrid[0].size() - 1;

		//		int count = recur(0, 0, obstacleGrid);
		int count = dp3(x_bound + 1, y_bound + 1, obstacleGrid);
		return count;
	}

private:

	int dp1(int x, int y, vector<vector<int>>& obstacleGrid) {
		vector<vector<int>> dp(x, vector<int>(y, 0));

		dp[0][0] = obstacleGrid[0][0] == 0 ? 1 : 0;

		for (int i = 1; i < dp.size(); i++) {
			dp[i][0] = (obstacleGrid[i][0] == 0 ? dp[i - 1][0] : 0);
		}

		for (int j = 1; j < dp[0].size(); j++) {
			dp[0][j] = (obstacleGrid[0][j] == 0 ? dp[0][j - 1] : 0);
		}

		for (int i = 1; i < dp.size(); i++) {
			for (int j = 1; j < dp[0].size(); j++) {
				if (obstacleGrid[i][j] == 0) {
					dp[i][j] += (dp[i - 1][j] + dp[i][j - 1]);
				}
				else {
					dp[i][j] = 0;
				}
			}
		}

		return dp[dp.size() - 1][dp[0].size() - 1];
	}

	int dp2(int x, int y, vector<vector<int>>& obstacleGrid) {
		vector<int> dp(y, 0);

		dp[0] = obstacleGrid[0][0] == 1 ? 0 : 1;

		for (int i = 1; i < obstacleGrid[0].size(); i++) {
			dp[i] = obstacleGrid[0][i] == 1 ? 0 : dp[i-1];
		}

		for (int i = 1; i < obstacleGrid.size(); i++) {
			dp[0] = obstacleGrid[i][0] == 1 ? 0 : dp[0];

			for (int j = 1; j < obstacleGrid[0].size(); j++) {
				if (obstacleGrid[i][j] == 0) {
					dp[j] += dp[j - 1];
				}
				else {
					dp[j] = 0;
				}
			}
		}

		return dp[dp.size()-1];
	}
 
    	int dp3(int x, int y, vector<vector<int>>& obstacleGrid) {
		vector<int> dp(y, 0);

		dp[0] = obstacleGrid[0][0] == 1 ? 0 : 1;
		
		for (int i = 0; i < obstacleGrid.size(); i++) {
			for (int j = 0; j < obstacleGrid[0].size(); j++) {
				if (obstacleGrid[i][j] == 1) dp[j] = 0;
				else if (j > 0) dp[j] += dp[j - 1];
				else {

				}
			}
		}

		return dp.back();
	}
    
	int recur(int x, int y, vector<vector<int>>& obstacleGrid) {

		if (x > x_bound || y > y_bound || obstacleGrid[x][y] == 1) {
			return 0;
		}

		if (x == x_bound && y == y_bound) {
			return 1;
		}

		return recur(x + 1, y, obstacleGrid) + recur(x, y + 1, obstacleGrid);
	}
private:
	int x_bound;
	int y_bound;
};
int main()
{
	vector<vector<int>> grid
	{
		//{1},
		//{0}
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 }
	};

	Solution sol;
	std::cout << sol.uniquePathsWithObstacles(grid) << std::endl;
}
