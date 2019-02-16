#include "header.h"
// 替换空格
// 思路：从后往前遍历
class Solution2 {
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