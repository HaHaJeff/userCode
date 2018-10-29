#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

struct Point {
     int x;
     int y;
	 Point() : x(0), y(0) {}
	 Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	int maxPoints(vector<Point>& points) {
		int max = 0;
		for (int i = 0; i < points.size(); ++i) {
			map<std::pair<int, int>, int> slopes;
			int duplicate = 1;
			for (int j = i + 1; j < points.size(); ++j) {
				if (points[j].x == points[i].x && points[j].y == points[i].y) {
					duplicate += 1;
					continue;
				}
				int y = points[j].y - points[i].y;
				int x = points[j].x - points[i].x;
				int gcd = generateGCD(x, y);
				if (gcd != 0) {
					y /= gcd;
					x /= gcd;
				}
				slopes[std::pair<int, int>(x, y)]++;
			}
			max = std::max(max, duplicate);
			for (auto slope : slopes) {
				max = std::max(slope.second + duplicate, max);
			}
		}

		return max;
	}

	int generateGCD(int a, int b) {
		if (b == 0) return a;
		else return generateGCD(b, a%b);
	}
};

int main() {
	Solution sol;

	vector<Point> points = { { 0, 0 }, { 94911151, 94911150 }, { 94911152, 94911151 } };

	std::cout << sol.maxPoints(points) << std::endl;
}
