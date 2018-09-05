#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
class Solution {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_set<string> repeated;
		unordered_set<string> seen;
		vector<string> results;
		int size = s.size();
		for (int i = 0; i <= size - 10; i++) {
			string str = s.substr(i,10);

			if (seen.emplace(str).second == false) {
				repeated.emplace(str);
			}
		}

		results.assign(repeated.begin(), repeated.end());

		return results;
	}
};

int main()
{
	string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
	Solution sol;
	vector<string> results = sol.findRepeatedDnaSequences(s);
	copy(results.begin(), results.end(), ostream_iterator<std::vector<string>::value_type>(std::cout, "\n"));
}
