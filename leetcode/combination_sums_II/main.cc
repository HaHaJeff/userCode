class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		vector<vector<int>> results;
		vector<int> result;
		std::sort(candidates.begin(), candidates.end());
		
		backtrace(candidates, results, result, 0, target);
		return results;
	}

	void backtrace(const vector<int>& candidates, vector<vector<int>>& results, vector<int>& result, int begin, int target) {
		if (target == 0) {
			results.push_back(result);
			return;
		}
		for (int i = begin; i < candidates.size(); ++i) {
			if (i > begin && candidates[i] == candidates[i - 1] || candidates[i] > target) {
				continue;
			}
			result.push_back(candidates[i]);
			backtrace(candidates, results, result, i + 1, target - candidates[i]);
			result.pop_back();
		}
	}
};
