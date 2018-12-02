#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		stringstream ss;
		string fraction = (numerator * denominator < 0) ? "-" : "+";

		long long result = numerator / denominator;
		long long remainder = numerator % denominator;

		intToString(ss, result);

		fraction += ss.str();
		unordered_map<long long, size_t> table;
		fraction += '.';
		while (remainder && table.find(result) != table.end()) {
			table.emplace(result, fraction.size());
			result = remainder * 10 / denominator;
			remainder = remainder * 10 % denominator;
			fraction += static_cast<char>(result + '0');
		}

		return fraction;
	}

	inline void intToString(stringstream& ss, long long num) {
		ss << num;
	}
};
