class Solution {
public:
    bool canReorderDoubled(vector<int>& A) {
        unordered_map<int, int> hash;
        for (auto& a : A) {
            hash[a]++;
        } 
        vector<int> keys;
        for (auto& h : hash) {
            keys.push_back(h.first);
        }
        sort(keys.begin(), keys.end(), [](int i, int j) {return abs(i) < abs(j);});
        for (auto& key : keys) {
            if (hash[key] > hash[2*key]) return false;
            hash[2 * key] -= hash[key];
        }
        return true;
    }
};

