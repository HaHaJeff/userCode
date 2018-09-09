#include <vector>
#include <iostream>

using namespace std;

// 区域分解法：sumRegion(int row1, int col1, int row2, int col2) = region(row2, col2) - region(row1, col2) - region(row2, col1) + region(row1, col1)
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> matrix) : matrix_(matrix), dp_(matrix){
		int rows = matrix.size();
		int cols = matrix[0].size();
		for (int i = 1; i < cols; ++i) {
			dp_[0][i] += dp_[0][i - 1];
		}
		for (int i = 1; i < rows; ++i) {
			dp_[i][0] += dp_[i - 1][0];
		}

		for (int i = 1; i < rows; ++i) {
			for (int j = 1; j < cols; ++j) {
				dp_[i][j] += dp_[i - 1][j] + dp_[i][j - 1] - dp_[i - 1][j - 1];
			}
		}

	}
	int sumRegion(int row1, int col1, int row2, int col2) {
		return dp_[row2][col2] - dp_[row1-1][col2] - dp_[row2][col1-1] + dp_[row1-1][col1-1];
	}

private:
	vector<vector<int>> matrix_;
	vector<vector<int>> dp_;
};
