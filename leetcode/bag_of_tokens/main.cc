class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        int i = 0, j = tokens.size()-1;
        int point = 0, result = 0;
        sort(tokens.begin(), tokens.end());
        while(i < j) {
            if (P >= tokens[i]) {
                P -= tokens[i];
                point = max(result, ++point); 
            } else if (point > 0) {
                --point;
                P += tokens[j--];
            } else {
                break;
            }
        }
        return result;
    }
};
