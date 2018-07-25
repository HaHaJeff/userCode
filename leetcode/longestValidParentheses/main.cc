#include <iostream>
#include <string>
#include <vector>
using namespace std;

//DP
//   ()(())
//   012345
//dp 020024
//if str[i] == ')'
//  if str[i-1] == '(' dp[i] = dp[i-2]+2
//  else if str[i-1] == ')'
//      if str[i-1-dp[i-1]] == '(' dp[i] = dp[i-1]+2+dp[i-1-dp[i-1]-1]
class Solution {
public:
    int longestValidParentheses(string s) {
        int max = 0;
        int len = s.size();
        vector<int> dp(len, 0);

        for (int i = 1; i < len; i++) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = dp[i-2]+2;
                    max = std::max(dp[i], max);
                }
                else {
                    if (i-1-dp[i-1] >= 0 && s[i-1-dp[i-1]] == '(') {
                        dp[i] = dp[i-1]+2+dp[i-1-dp[i-1]-1];
                        max = std::max(dp[i], max);
                    }
                }
            }
        }
        return max;
    }
};

int main()
{
    Solution sol;

    string str = "()(())(())";

    cout << sol.longestValidParentheses(str);
}
