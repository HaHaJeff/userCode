#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

class Solution {
public:
	string fractionToDecimal(long long numerator, long long denominator) {
		stringstream ss;
		string fraction = (numerator * denominator < 0) ? "-" : "";
		numerator = abs(numerator);
		denominator = abs(denominator);
		long long result = numerator / denominator;
		long long remainder = numerator % denominator;

		intToString(ss, result);

		fraction += ss.str();

		if (remainder == 0) { return fraction; }
		std::unordered_map<long long, size_t> table;
		fraction += '.';
		while (remainder && table.find(remainder) == table.end()) {
			table.emplace(remainder, fraction.size());
			result = remainder * 10 / denominator;
			remainder = remainder * 10 % denominator;
			fraction += static_cast<char>(result + '0');
		}

		if (remainder != 0) {
			fraction.insert(table[remainder], 1, '(');
			fraction += ')';
		}
		return fraction;
	}

	inline void intToString(stringstream& ss, long long num) {
		ss << num;
	}
};
