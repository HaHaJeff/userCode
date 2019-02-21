class Solution {
public:
int numberOfArithmeticSlices(vector<int>& A) {
    if(A.empty()) return 0;
    vector<unordered_map<int,int>> dp(A.size());//[index, [difference, count]]
    
    int res = 0;
    for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < i; ++j){
            if((long)A[i] - (long)A[j] > INT_MAX || (long)A[i] - (long)A[j] < INT_MIN) continue;// do not ignore this step, it will help you save time & space to pass OJ.
            int dif = A[i] - A[j];
            // 以i结尾，差为dif的统计
            dp[i][dif] += 1;  
            if(dp[j].find(dif) != dp[j].end()){
                dp[i][dif] += dp[j][dif];
                res += dp[j][dif];   // dp[j][dif]包括序列数为2的，所以以i结尾的就是dp[j][dif]的值，不需要+1
            }
        }
    }
    return res;
}
};
