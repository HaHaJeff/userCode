// backstrace leetcode time limited
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return vector<string>();
        vector<string> result;
        if (find(wordDict.begin(), wordDict.end(), s) != wordDict.end())
            result.push_back(s);
        for (int i = 1; i <= s.size(); i++) {
            string left = s.substr(0, i);
            if (find(wordDict.begin(), wordDict.end(), left) != wordDict.end()) {
                string right = s.substr(i);
                vector<string> next = wordBreak(right, wordDict);
                
                for (auto str : next) {  
                    result.push_back(left + " " + str);    
                }
            }
        }
        
        return result;
    }
};


/*
Runtime: 60 ms, faster than 6.63% of C++ online submissions for Word Break II.
Memory Usage: 20.2 MB, less than 6.66% of C++ online submissions for Word Break II.
*/
class Solution {
private:
    std::map<string, vector<string>> cache;
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (cache.find(s) != cache.end()) return cache[s];
        if (s.empty()) return vector<string>();
        vector<string> result;
        if (find(wordDict.begin(), wordDict.end(), s) != wordDict.end())
            result.push_back(s);
        for (int i = 1; i <= s.size(); i++) {
            string left = s.substr(0, i);
            if (find(wordDict.begin(), wordDict.end(), left) != wordDict.end()) {
                string right = s.substr(i);
                vector<string> next = wordBreak(right, wordDict);
                
                for (auto str : next) {  
                    result.push_back(left + " " + str);    
                }
            }
        }
        cache[s] = result;
        
        return result;
    }
};

/*
Runtime: 16 ms, faster than 90.31% of C++ online submissions for Word Break II.
Memory Usage: 12 MB, less than 78.09% of C++ online submissions for Word Break II.
*/
class Solution {
private:
    std::unordered_map<string, vector<string>> cache;
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) { 
        if (s.empty()) return {""};
        if (cache.find(s) != cache.end()) return cache[s];
        vector<string> result;
        for (auto& str : wordDict) {
            if (s.substr(0, str.size()) != str) continue;
            vector<string> res = wordBreak(s.substr(str.size()), wordDict);
            for (auto& r : res) {
                result.push_back(str+(r.empty()?"":" ")+r);
            }
        } 
        cache[s] = result;
        return result;
    }
};
