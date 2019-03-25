class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        std::unordered_map<string, int> countMap;
        for(auto& word : words) {
            countMap[word]++;
        }
        std::vector<pair<string, int>> countVec(countMap.begin(), countMap.end());
        auto comp = [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
            return lhs.second > rhs.second || (lhs.second == rhs.second && lhs.first < rhs.first);
        };
        std::priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(comp)> q(comp);
        for (auto& item : countVec) {
            q.push(item);
            if (q.size() > k) q.pop();
        }
        std::vector<string> output;
        while(!q.empty()) {
            output.insert(output.begin(), q.top().first);
            q.pop();
        }
        return output;
    }
};
