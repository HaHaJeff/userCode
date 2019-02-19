class Solution {
public:
    void insertArray(vector<int>& array, int start, int end) {
        for (int i = end; i > start; i--) {
            swap(array[i], array[i-1]);
        }
    }
    void reOrderArray(vector<int> &array) {
        int i = 0, j = 0;
        while(j < array.size()) {
            if (array[j] & 1) {
                insertArray(array, i++, j);
            }
            j++;
        }
    }

};
