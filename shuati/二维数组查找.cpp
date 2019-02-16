#include "header.h"

// 二维数组查找
//思路：从左下角开始遍历，缩小查找范围
class Solution1 {
public:
	bool Find(int target, vector<vector<int> > array) {
		int row = array.size() - 1;
		int col = array[0].size() - 1;

		for (int i = row, j = 0; i >= 0 && j <= col;) {
			if (target == array[i][j]) return true;
			else if (target > array[i][j]) j++;
			else  i--;
		}
		return false;
	}
};