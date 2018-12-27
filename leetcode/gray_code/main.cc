class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> results;
		int s = pow(2, n);
		for (int i = 0; i < s; ++i) {
			results.push_back(i ^ (i >> 1));
		}

		return results;
	}
};
