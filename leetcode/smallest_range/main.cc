class Solution {
public:
	typedef pair < vector<int>::iterator, vector<int>::iterator >  Elem;

	struct comp {
		bool operator()(Elem& e1, Elem& e2) {
			return *e1.first > *e2.first;
		}
	};
	// 0 9 12 20
	// 4 10 15 24 26
	// 5 18 22 30
	// push 0 4 5
	// pop 0, push 9, 4, 5, 9 以此类推
	// ... 20 22 24
	vector<int> smallestRange(vector<vector<int>>& nums) {

		priority_queue<Elem, vector<Elem>, comp> pq;

		// 0, 4, 5
		//
		int lo = INT_MAX, hi = INT_MIN;
		for (auto& row : nums) {
			lo = min(row[0], lo);
			hi = max(row[0], hi);
			pq.push({row.begin(), row.end()});
		}

		vector<int> ans = { lo, hi };

		while (true) {

			auto p = pq.top();
			pq.pop();
			++p.first;
			//说明该vector已经遍历结束
			if (p.first == p.second) {
				break;
			}
			// push 该vector的下一个元素
			pq.push(p);

			// 更新 lo hi, 更新hi只需要将hi与新push的元素比较即可
			lo = *pq.top().first;
			hi = max(hi, *p.first);

			if (hi - lo < ans[1] - ans[0]|| ((hi - lo) == (ans[1] - ans[0])) && lo < ans[0]) {
				ans = { lo, hi };
			}
		}

		return ans;
	}
};

