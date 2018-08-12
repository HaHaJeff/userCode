#include <iostream>
#include <string>
#include <vector>
class Solution {
public:
  std::string longestCommonPrefix(std::vector<std::string>& strs) {
    int max = 0;

    for (auto str : strs) {
      max = max < str.size() ? str.size() : max;
    }

       std::vector<std::vector<int>> dic(max, std::vector<int>(26));

        for(auto word : strs) {
            int index = 0;

            for (auto ch : word)
                dic[index++][ch-'a']++;
        }

        int size = strs.size();
        std::string longest_str;

        for (auto item : dic) {
            int index = 0;
            for (; index<item.size();index++) {
                if (item[index] == size) {
                    longest_str.push_back(static_cast<char>(index+'a'));
                    break;
                }
            }
            if (index == item.size()) break;
        }
        return longest_str;
    }
};



int main()
{
  Solution sol;
  std::vector<std::string> strs{"flower", "flow", "flight"};
  std::cout << sol.longestCommonPrefix(strs) << std::endl;
}
