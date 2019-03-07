class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        int peakL = 0, peakR = A.size() - 1, len = A.size();
        while (peakL < len - 1 && A[peakL] < A[peakL+1]) peakL++;
        while (peakR > 0 && A[peakR] < A[peakR-1]) peakR--;
        return peakL == peakR && peakL != 0 && peakR != A.size()-1;
    }

};
