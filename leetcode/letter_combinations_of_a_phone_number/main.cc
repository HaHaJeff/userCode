// 用循环的思路解决递归
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> alp = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> results;
        if (digits.empty()) return results;
        
        results.push_back("");
        for (auto cnum : digits) {
            int index = cnum - '0';
            
            if (alp[index].empty()) continue;
            
            vector<string> tmp;
            for (auto ch : alp[index]) {
                for (auto c : results) {
                    tmp.push_back(c+ch);
                }
            }
            
            results.swap(tmp);
        }
        
        return results;
    }
};
