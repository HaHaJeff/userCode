class Solution {
public:
	int threeSumMulti(vector<int>& A, int target) {
		std::map<int, long> tuples;
		long cnt = 0;
		// 记录每个数字出现的次数
		for (auto& a : A) {
			tuples[a]++;
		}

		//大前提 i <= j <= k这样才能保证不出现重复组合
		//1. 三个数字都相等，此时可选的组合数：C(i, 3);
		//2. 两个数字相等 ，此时可选的组合数：C(i,2) * C(k,1) + C(j,2) * C(i,1)
		for (auto&it1 : tuples) {
			for (auto&it2 : tuples) {
				auto i = it1.first, j = it2.first, k = target - i - j;
				if (!tuples.count(k)) continue;
				if (i == j && j == k) cnt += tuples[i] * (tuples[i] - 1) * (tuples[i] - 2) / 6;
				else if (i == j && j < k) cnt += tuples[i] * (tuples[i] - 1) / 2 * tuples[k];
				else if (i < j && j == k) cnt += tuples[i] * tuples[j]%static_cast<int>(1e9 + 7) * (tuples[j] - 1) / 2;
				else if (i < j && j < k) cnt += tuples[i] * tuples[j] * tuples[k];
			}
		}
		return cnt%static_cast<int>(1e9 + 7);
	}
};
