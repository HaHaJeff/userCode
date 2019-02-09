class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> results;
        
        helper(results, S, 0);
        
        return results;
    }
    
    void helper(vector<string>& results, string& s, int start) {
        if (start == s.size()) {
            results.push_back(s);
            return;
        }
        helper(results, s, start+1);
        if (!isalpha(s[start])) return;
        if (s[start] >= 'a' && s[start] <= 'z') s[start] = toupper(s[start]);
        else s[start] = tolower(s[start]);
        helper(results, s, start+1);
        if (s[start] >= 'A' && s[start] <= 'Z') s[start] = toupper(s[start]);
        else {s[start] = tolower(s[start]);}
        
    }
};



