class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		queue<string> toVisit;
		auto iter = find(wordList.begin(), wordList.end(), endWord);
		if (iter == wordList.end()) return 0;
		push(beginWord, wordList, toVisit);
		int dist = 2;
		while (!toVisit.empty()) {
			int num = toVisit.size();

			// BFS
			for (int i = 0; i < num; i++) {
				auto elem = toVisit.front();
				toVisit.pop();
				if (elem == endWord) return dist;
				push(elem, wordList, toVisit);
			}
			dist++;
		}
		return dist;
	}

	void push( string& word, vector<string>& wordList, queue<string>& toVisit){

		auto iter = find(wordList.begin(), wordList.end(), word);
		if (iter != wordList.end())
			wordList.erase(iter);
		
		for (int pos = 0; pos < word.size(); pos++) {
			char letter = word[pos];

			for (int i = 0; i < 26 && !wordList.empty(); i++) {
				word[pos] = 'a' + i;
				auto iter = find(wordList.begin(), wordList.end(), word);
				if (iter != wordList.end()) {
					toVisit.push(*iter);
					wordList.erase(iter);
				}
			}

			word[pos] = letter;
		}

	}
};
