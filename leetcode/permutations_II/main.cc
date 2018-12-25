class Solution1 {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {

		vector<vector<int>> results;
		vector<int> result;
		std::sort(nums.begin(), nums.end());
		backtrace(nums, results, 0);
		return results;
	}

	void backtrace(vector<int>& nums, vector<vector<int>>& results, int begin) {

		if (begin == nums.size()-1) {
			results.push_back(nums);
			return;
		}

		for (int i = begin; i < nums.size(); i++) {
			if (i != begin && nums[i] == nums[begin]) continue;
			swap(nums[begin], nums[i]);
			backtrace(nums, results, begin + 1);
		//	swap(nums[begin], nums[i]);
		}
	}
};

class Solution {
public:
	void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) {
		if (i == j - 1) {
			res.push_back(num);
			return;
		}
		for (int k = i; k < j; k++) {
			if (i != k && num[i] == num[k]) continue;
			swap(num[i], num[k]);
			recursion(num, i + 1, j, res);
		}
	}
	vector<vector<int> > permuteUnique(vector<int> &num) {
		sort(num.begin(), num.end());
		vector<vector<int> >res;
		recursion(num, 0, num.size(), res);
		return res;
	}
};

class Solution {
public:
	void recursion(vector<int>& num, int i, int j, vector<vector<int> > &res) {
		if (i == j - 1) {
			res.push_back(num);
			return;
		}
		for (int k = i; k < j; k++) {
			int z = 0;
			for (z = i; z < k; z++) {
				if (z != k && num[z] == num[k]) break;
			}
			if (z < k) {
				continue;
			}
			
			swap(num[i], num[k]);
			recursion(num, i + 1, j, res);
			swap(num[i], num[k]);
		}
	}
	vector<vector<int> > permuteUnique(vector<int> &num) {
		sort(num.begin(), num.end());
		vector<vector<int> >res;
		recursion(num, 0, num.size(), res);
		return res;
	}
};
