#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty()) return false;
		int row = matrix.size() - 1;
		int col = 0;

		while (col < matrix[0].size() && row >= 0) {
			if (target < matrix[row][col]) {
				--row;
			}
			else if (target > matrix[row][col]) {
				++col;
			}
			else {
				return true;
			}
		}
		return false;
	}
};
