#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	void solveSudoku(vector<vector<char>> &broad) {
		if (broad.size() == 0) return;

		solveCore(broad);
	}

private:
	bool solveCore(vector<vector<char>> &broad) {
		for (int i = 0; i < broad.size(); i++) {
			for (int j = 0; j < broad[0].size(); j++) {
				if (broad[i][j] == '.') {
					for (char c = '1'; c <= '9'; c++) {
						if (isValid(i, j, c, broad)) {
							broad[i][j] = c;

							if (solveCore(broad)) return true;
							else broad[i][j] = '.';
						}
					}
					return false;
				}
			}
		}
		return true;
	}

	bool isValid(int row, int col, char ch, vector<vector<char>> &broad) {
		int sub_row = row / 3 * 3;
		int sub_col = col / 3 * 3;
		//
		//for (int i = 0; i < 9; i++) {
		//	char block_ch = broad[sub_row + i / 3][sub_col + i % 3];
		//	char col_ch = broad[row][i];
		//	char row_ch = broad[i][col];

		//	//row is valid
		//	if (row_ch != '.' && row_ch == ch) return false;

		//	//col is valid
		//	if (col_ch != '.' && col_ch == ch) return false;

		//	// sub block is valid?
		//	if (block_ch != '.' && block_ch == ch) return false;
		//}

		for (int i = 0; i < 9; i++) {
			//row is valid
			if (broad[i][col] != '.' && broad[i][col] == ch) return false;

			//col is valid
			if (broad[row][i] != '.' && broad[row][i] == ch) return false;

			// sub block is valid?
			if (broad[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] != '.' && broad[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == ch) return false;
		}

		return true;
	}
};

int main(){
	Solution sol;
	vector<vector<char>> broad
	{
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
	};

	sol.solveSudoku(broad);

	std::for_each(broad.begin(), broad.end(), [&](vector<char> item) {
		std::for_each(item.begin(), item.end(), [&](char ch){std::cout << "\"" << ch << "\"" << ","; });
		std::cout << "\n";
	});

}
