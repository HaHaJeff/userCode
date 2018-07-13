#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        vector<vector<string>> vec{
            {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
            {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
            {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
            {"", "M", "MM", "MMM"}
        };
        return vec[3][num/1000]+vec[2][(num%1000)/100]+vec[1][(num%100)/10]+vec[0][(num%10)];
    }
};

int main(int argc, char** argv)
{
	Solution sol;
  int num = atoi(argv[1]);
	cout << sol.intToRoman(num) << endl;
}
