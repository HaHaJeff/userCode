Given a string, find the length of the longest substring without repeating characters.

Examples:
```
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

``` cpp
class Solution {
public:
    //思路：利用额外空间存储当前字符出现过，i为此时字符串的下标，只要取得字串的开始下标即可
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndexAsSize(256);               //将每一个字符的ascii值作为下标使用，且这个下标代表的就是字串的长度
        int start = 0, maxLen = 0;                      //代表连续非重复字串的起始下标
        
        for(int i = 0; i < s.size(); i++)
        {
            if(charIndexAsSize[s[i]] > start )          //出现重复字符，更新start
                start = charIndexAsSize[s[i]];          //更新start，令start=前一个重复字符的下标
            
            charIndexAsSize[s[i]] = i + 1;              //i+1表示的长度
            maxLen = max(maxLen, i + 1 - start);        //更新最大长度
        }
        return maxLen;
    }
};
```
