class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> results;
        helper(board, results, 0);
        return results;
    }
    
    void helper(vector<string>& board, vector<vector<string>>&results, int row) {
        if (row == board.size()) {
            results.push_back(board);
            return;
        }
        
        for (int col = 0; col < board[0].size(); col++) {
            if (validate(board, row, col)) {
                board[row][col] = 'Q';
                helper(board, results, row+1);
                board[row][col] = '.';    
            }
        }
    }
    
    bool validate(vector<string>& board, int row, int col) {
        for(int i = 0; i < row; i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == 'Q' && board[i][col] == 'Q') return false;
                if (board[i][j] == 'Q' && (i+col == j+row || i+j==row+col)) return false;
            }
        }
        return true;
    }
};
