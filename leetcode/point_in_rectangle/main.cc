#include <iostream>

using namespace std;

// 对于矩形的边平行于XY坐标系的直接判断即可
// 对于不平行于坐标系的矩形必须旋转坐标轴至与矩形平行
class Solution {
public:
	
	bool isInSide(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y) {
		if (y1 == y2) { return isInSide(x1, y1, x4, y4, x, y); }

		//旋转
		double l = abs(y4 - y1);
		double k = abs(x4 - x1);
		double s = sqrt(l*l + k*k);

		double sin = l / s;
		double cos = k / s;

		double x1R = cos*x1 + sin*y1;
		double y1R = -x1*cos + y1*sin;
		double x4R = cos*x4 + sin*y4;
		double y4R = -x4*cos + y4*sin;
		double xR = cos*x + sin*y;
		double yR = -x*cos + y*sin;

		return isInSide(x1R, y1R, x4R, y4R, xR, yR);
	}

	bool isInSide(double x1, double y1, double x4, double y4, double x, double y) {
		if (x <= x1 || x >= x4 || y <= y1 || y >= y4) {
			return false;
		}
		return true;
	}


private:
};

int main()
{
	Solution sol;
	std::cout << sol.isInSide(1, 0, 1, 8, -2, 4, 4, 4, 1, 1) << std::endl;
}

