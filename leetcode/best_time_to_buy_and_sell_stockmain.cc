class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int minPrice = INT_MAX;
		int maxProfit = 0;

		for (auto price : prices) {
			if (minPrice > price) {
				minPrice = price;
			}
			else if (price-minPrice > maxProfit) {
				maxProfit = price - minPrice;
			}
		}

		return maxProfit;
	}
};
