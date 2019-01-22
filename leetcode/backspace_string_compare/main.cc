class Solution1 {
public:
    
    bool backspaceCompare(string S, string T) {
        
        stack<char, vector<char>> sS, sT;
        for (auto& c : S) {
            if (c == '#' && !sS.empty()) {
                sS.pop();
            } else if (c != '#') {
                sS.push(c);
            }
        }
        
        for (auto& c : T) {
            if (c == '#' && !sT.empty()) {
                sT.pop();
            } else if (c != '#') {
                sT.push(c);
            } 
        }
        
        return sS == sT; 
    }
};

class Solution {
public:
    
    bool backspaceCompare(string S, string T) {
        int back = 0, i = S.size()-1, j = T.size() - 1;
        while(true) {
            while (i >= 0 && (S[i] == '#' || back > 0)) {
                back += S[i] == '#' ? 1 : -1;
                i--;
            }
            while (j >= 0 && (T[j] == '#' || back > 0)) {
                back += T[j] == '#' ? 1 : -1;
                j--;
            }
            if (i >= 0 && j >= 0 && S[i] == T[j]) {
                --i; --j;
            } else return i == -1 && j == -1;
            
        }
        
    }
};
