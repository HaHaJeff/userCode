#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    bool checkValidString(string s) { 
        if (s.empty()) return true;
        bool flag = false;
        for (auto& ch : s) {
            flag |= ch == '*' ? true : false;
        }
        if (flag) return dfs(s, 0);
        return valid(s);
    }
    
    bool dfs(string& s, int i) {
        if (i >= s.size()) {
            std::cout << s << std::endl;
            return valid(s);
        }
        bool res = false;
        if (s[i] == '*') {
            s[i] = '('; res |= dfs(s, i+1);
            //if (res) return res;
            s[i] = ')'; res |= dfs(s, i+1);
            //if (res) return res;
            s[i] = '#'; res |= dfs(s, i+1);
        } else {
            res |= dfs(s, i+1);
        }
      
        return res;
    }
    
    bool valid(string& s) {
        int left = 0, right = 0;
        for (auto& ch : s) {
            if (ch == '(') left++;
            else if (ch == ')') left--;
            if (left < 0) return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.checkValidString("((((()(()()()*()(((((*)()*(**(())))))(())()())(((())())())))))))(((((())*)))()))(()((*()*(*)))(*)()");
}
