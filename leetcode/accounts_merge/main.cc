class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> email_root;
        vector<int> union_find(accounts.size(), 0);
        
        for (int i = 0; i < accounts.size(); i++) {
            union_find[i] = i;
            for (int j = 1; j < accounts[i].size(); j++) {
                if(email_root.find(accounts[i][j]) == email_root.end()) {
                    email_root[accounts[i][j]] = union_find[i];
                } else {
                    auto root1 = find(union_find, i);
                    auto root2 = find(union_find, email_root[accounts[i][j]]);
                    union_find[root1] = root2;
                }
            }
        }
        unordered_map<int, vector<string>> res_map;
        for (auto& pair : email_root) {
            int idx = find(union_find, pair.second);
            res_map[idx].push_back(pair.first);
        }
        
        vector<vector<string>> res;
        for (auto& it : res_map) {
            vector<string> email = it.second;
            sort(email.begin(), email.end());
            email.insert(email.begin(), accounts[it.first][0]);
            res.push_back(email);
        }
        return res;
    }
    
    int find(vector<int>& union_find, int idx) {
        while(union_find[idx] != idx) {
            idx = union_find[idx];
        }
        return idx;
    }
};
