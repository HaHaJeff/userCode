// 二维数组查找
//思路：从左下角开始遍历，缩小查找范围
class Solution {
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
// 替换空格
// 思路：从后往前遍历
class Solution {
public:
	void replaceSpace(char *str, int length) {
		int space_cnt = 0;
		int old_end = 0, new_end = 0;
		while (str[old_end] != '\0') {
			if (str[old_end++] == ' ') space_cnt++;
		}
		int inc_size = space_cnt * 2;
		new_end = old_end + inc_size;
		while (old_end >= 0) {
			if (str[old_end] == ' ') {
				str[new_end--] = '0';
				str[new_end--] = '2';
				str[new_end--] = '%';
			}
			else {
				str[new_end--] = str[old_end];
			}
			--old_end;
		}
	}
};
