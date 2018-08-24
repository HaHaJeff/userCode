#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int numIslands(vector<vector<char>>& grid) {

		int count = 0;
		for (int i = 0; i < grid.size(); ++i){
			for (int j = 0; j < grid[0].size(); ++j) {
				if (grid[i][j] == '1') {
					count += 1;
					dfs(grid, i, j);
				}
			}
		}

		return count;
	}

	void dfs(vector<vector<char>>& grid, int i, int j) {
		if (i >= grid.size() || j >= grid[0].size() || i < 0 || j < 0 || grid[i][j] == '0') {
			return;
		}
		grid[i][j] = '0';
		dfs(grid, i, j + 1);
		dfs(grid, i, j - 1);
		dfs(grid, i + 1, j);
		dfs(grid, i - 1, j);
	}
};

int main()
{
	vector<vector<char>> grid = {
		{ '1', '1', '0', '0', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' }
	};

	Solution sol;
	int num = sol.numIslands(grid);
	std::cout << num << std::endl;
}
