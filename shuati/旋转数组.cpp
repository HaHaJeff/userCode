#include "header.h"
//旋转数组
//思路：采用二分法求解
//1. 如果mid > high，说明最小值一定在[mid+1, high] 
//2. 如果mid < high,说明最小值一定在[low, mid]  
//3. 如果mid == high，则无法判断最小值实在mid左边或右边，只能--high
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.empty()) return 0;
		int start = 0, end = rotateArray.size() - 1, mid = 0;
		while (start < end) {
			mid = start + (end - start) / 2;
			if (rotateArray[mid] > rotateArray[end]) start = mid + 1;
			else if (rotateArray[mid] < rotateArray[end])end = mid;
			else --end;
		}
		return rotateArray[start];
	}
};