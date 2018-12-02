#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		stringstream ss;
		string fraction = (numerator * denominator < 0) ? "-" : "";

		long long result = numerator / denominator;
		long long remainder = numerator % denominator;

		intToString(ss, result);

		fraction += ss.str();
        std::unordered_map<long long, size_t> table;
		fraction += '.';
		while (remainder && table.find(result) == table.end()) {
			result = remainder * 10 / denominator;
			remainder = remainder * 10 % denominator;
			fraction += static_cast<char>(result + '0');
			table.emplace(result, fraction.size() - 1);
		}

        if (remainder!= 0) {
            fraction.insert(table[result], 1, '(');
            fraction += ')';
        }
		return fraction;
	}

	inline void intToString(stringstream& ss, long long num) {
		ss << num;
	}
};

int main()
{
    Solution sol;
    std::cout << sol.fractionToDecimal(4, 6) << std::endl;

}
