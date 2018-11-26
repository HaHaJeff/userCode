// O(n) time complexity
// O(1) space complexity
class Solution {
public:

	void reverseWords(string &s) {
		if (s.empty()) return;

		int start = 0, end = s.size() - 1;

		while (start < end) {
			swap(s[start++], s[end--]);
		}

		int word_start = 0, word_end = s.size()-1;

        //reduce multiple tail spaces 
		while (word_end >= 0 && s[word_end] == ' ') { word_end--; }
		s.erase(word_end+1, s.size() - word_end - 1);

		word_start = 0, word_end = s.size() - 1;

		while (word_start < s.size()) {

			// reduce multiple spaces between two words 
			int space_start = word_start, space_end = word_start;
			while (space_end < s.size() && s[space_end] == ' ') { space_end++; }
			s.erase(space_start, space_end - space_start);

			// find the end of valid word
			word_end = word_start + 1;
			while (word_end < s.size() && s[word_end] != ' ') { word_end++; }

			// reverse valid word
			int tmp_start = word_start, tmp_end = word_end - 1;
			while (tmp_start < tmp_end) {
				swap(s[tmp_start++], s[tmp_end--]);
			}

			word_start = word_end + 1;
		}
	}
};
