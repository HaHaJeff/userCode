/*************************************************************************
    > File Name: main.cpp
    > Author: MSGF_NGINX
    > Mail: 327767852@qq.com
    > Created Time: 2017年09月06日 星期三 09时48分01秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// Example 1:
// nums1 = [1, 3]
// nums2 = [2]
// the median is 2.0
// *********************
// Example 2:
// nums1 = [1, 2]
// nums2 = [3, 4]
// the median is 2.5 (2 + 3)/2
// requirement: run time complerxity shoudle be O(log(m + n))


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        vector<int>::iterator begin1 = nums1.begin();
        vector<int>::iterator begin2 = nums2.begin();
        
        int medainIndex = (size1 + size2 + 1)/2;
        
        //shoudle consider which is the end
        //> len
        for(int i = 1; i < medainIndex; i++) {
            
            
        }
        
        if(medainIndex & 1 == 0) return (*begin1 + *begin2)/2;
        else return 0.0;
    }
};
