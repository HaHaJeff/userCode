#include <iostream>

using namespace std;

// 向量叉乘，右手法则，食指指向第一个向量，中指指向第二个向量
// 大拇指指向结果向量，若点O在三角形ABC内部，对于AB来说，O点和C点在AB的一侧
// 同理，对于其他两点亦是如此，方向是否在一侧可以根据右手法则判断
class Solution {
public:
	bool isInSide(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y) {

		if (crossProduct(x2 - x1, y2 - y1, x - x1, y - y1) * crossProduct(x2 - x1, y2 - y1, x3 - x1, y3 - y1) < 0) {
			return false;
		}
		if (crossProduct(x3 - x1, y3 - y1, x - x1, y - y1) * crossProduct(x3 - x1, y3 - y1, x2 - x1, y2 - y1 ) < 0) {
			return false;
		}
		if (crossProduct(x3 - x2, y3 - y2, x - x2, y - y2) * crossProduct(x3 - x2, y3 - y2, x1 - x2, y1 - y2) < 0) {
			return false;
		}
		return true;
	}


	//x1表示向量A的X，y1表示向量A的y
	double crossProduct(double x1, double y1, double x2, double y2) {
		return x1*y2 - x2*y1;
	}
private:
};

int main()
{
	Solution sol;
	std::cout << sol.isInSide(0, 0, 2, 0, 0, 2, 3, 3) << std::endl;
}

