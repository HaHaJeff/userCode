class Solution {
public:
    int longestMountain(vector<int>& A) {
        vector<int> down(A.size(), 0);
        vector<int> up(A.size(), 0);
        for (int i = A.size()-2; i >= 0; i--) {
            if (A[i] > A[i+1]) down[i] = down[i+1] + 1;
        }
        int maxLen = 0;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] > A[i-1]) up[i] = up[i-1]+1;
            if (up[i] && down[i]) {
                maxLen = max(maxLen, up[i]+down[i]+1);
            }
        }
        return maxLen;
    }
};
