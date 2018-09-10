#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// sell must after buy
// after sell, buy can't occur at next day
// sell[i] = max(buy[i-1]+price, sell[i-1])  means that buy stock at day(i-1) and sell it at day(i) or don't sell it at day(i)
// buy[i]  = max(rest[i-1]-price, buy[i-1])  means that rest at day(i-1) and buy it at day(i) or don't buy  it at day(i)
// rest[i] = max(buy[i-1], sell[i-1], rest[i-1])
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int size = prices.size();
		vector<int> buy(size, 0);
		vector<int> sell(size, 0);
		vector<int> rest(size, 0);

		buy[0] = -prices[0];

		for (int i = 1; i < size; i++) {
			buy[i] = std::max(rest[i - 1] - prices[i], buy[i - 1]);
			sell[i] = std::max(buy[i - 1] + prices[i], sell[i - 1]);
			rest[i] = std::max(buy[i - 1], std::max(sell[i - 1], rest[i - 1]));
		}
		return sell[size - 1];
	}
};

int main()
{
	Solution sol;
	vector<int> prices = {1,2,3,0,2};
	std::cout << sol.maxProfit(prices) << std::endl;
}
