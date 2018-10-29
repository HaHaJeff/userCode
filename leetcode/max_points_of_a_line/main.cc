#include <vector>
#include <unordered_map>
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
			unordered_map<double, int> slopes;
			int duplicate = 1;
			for (int j = i + 1; j < points.size(); ++j) {
				if (points[j].x == points[i].x && points[j].y == points[i].y) {
					duplicate += 1;
					continue;
				}

				double slope = (points[j].x == points[i].x) ? INT_MAX :
					((double)points[j].y - points[i].y) / (points[j].x - points[i].x);
				slopes[slope]++;
			}
			max = std::max(max, duplicate);
			for (auto slope : slopes) {
				max = std::max(slope.second + duplicate, max);
			}
		}

		return max;
	}


};

int main() {
	Solution sol;

	vector<Point> points = { { 0, 0 }, { 94911151, 94911150 }, { 94911152, 94911151 } };

	std::cout << sol.maxPoints(points) << std::endl;
}
