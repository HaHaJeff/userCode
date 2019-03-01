class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<int> dp(s.size()+1);
        dp[0] = 1;
        for(int i = 1; i <= s.size(); i++) {
            for (int j = i-1; j >= 0; j--) {
                if (dp[j] && dict.find(s.substr(j, i-j)) != dict.end()) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};
