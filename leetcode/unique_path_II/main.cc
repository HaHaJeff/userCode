class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		x_bound = obstacleGrid.size() - 1;
		y_bound = obstacleGrid[0].size() - 1;

		int count = recur(0, 0, obstacleGrid);

		return count;
	}

private:
	int recur(int x, int y, vector<vector<int>>& obstacleGrid) {

		if (x > x_bound || y > y_bound || obstacleGrid[x][y] == 1 ) {
			return 0;
		}

		if (x == x_bound && y == y_bound) {
			return 1;
		}
        
        std::pair<int, int> point{x, y};
        
        if (done.find(point) != done.end()) return done[point];

		int tmp = recur(x + 1, y, obstacleGrid) + recur(x, y + 1, obstacleGrid);
        done.insert(std::pair<std::pair<int, int>, int>(point, tmp));
        return tmp;
	}
private:
	int x_bound;
	int y_bound;
    map<std::pair<int, int>, int> done;
};

