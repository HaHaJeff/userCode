#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
	string validIPAddress(string IP) {
		transform(IP.begin(), IP.end(), IP.begin(), ::tolower);
		if (IP.find(":") != string::npos) {
			return ipv6(IP) ? "IPv6" : "Neither";
		}
		else if (IP.find(".") != string::npos) {
			return ipv4(IP) ? "IPv4" : "Neither";
		}
		return "Neither";
	}

	bool ipv4(string IP) {
		int cnt = 0;
		function < bool(char)> isNumber = [](char c){return isdigit(c); };
		for (auto it = IP.begin(); it != IP.end();) {
			if (isNumber(*it)) {
				auto it2 = find_if_not(it, IP.end(), isNumber);

				if (it2 != IP.end() && *it2 != '.') {
					return false;
				}

				string sub = string(it, it2);

				if (sub.size() < 1 || sub.size() > 3 || (sub[0] == '0' && sub.size() > 1) || stoi(sub) > 255) {
					return false;
				}

				++cnt;

				if (cnt == 4 && it2 != IP.end()) { return false; }
				it = it2;
			}
			else {
				if (*it != '.') {
					return false;
				}
				it++;
				if (it != IP.end() && (*it) == '.') {
					return false;
				}
			}
		}
		return cnt == 4;
	}

	bool ipv6(string IP) {
		
		int cnt = 0;
		function < bool(char)> isHex = [](char c){return isdigit(c) || (c <= 'f' && c >= 'a'); };
		for (auto it = IP.begin(); it != IP.end();) {
			if (isHex(*it)) {
				auto it2 = find_if_not(it, IP.end(), isHex);

				if (it2 != IP.end() && *it2 != ':') {
					return false;
				}

				string sub = string(it, it2);

				if (sub.size() > 4) {
					return false;
				}

				++cnt;

				if (cnt == 8 && it2 != IP.end()) {
					return false;
				}

				it = it2;
			}
			else {
				if (*it != ':') {
					return false;
				}
				++it;
				if (it != IP.end() && *it == ':') {
					return false;
				}
			}
		}


		return cnt == 8;
	}
};

int main()
{
	std::string ipv4 = "192.0.0.1";

	Solution sol;
	std::cout << sol.validIPAddress(ipv4) << std::endl;
}
