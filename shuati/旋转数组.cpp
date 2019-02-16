#include "header.h"
//��ת����
//˼·�����ö��ַ����
//1. ���mid > high��˵����Сֵһ����[mid+1, high] 
//2. ���mid < high,˵����Сֵһ����[low, mid]  
//3. ���mid == high�����޷��ж���Сֵʵ��mid��߻��ұߣ�ֻ��--high
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