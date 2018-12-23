class Solution {
public:
	vector<string> restoreIpAddresses(string s) {

		int a = 0, b = 0, c = 0, d = 0;
		vector<string> results;

		if (s.empty() || s.size() < 4) {
			return results;
		}
		for (a = 1; a < 4 && a <= s.size() - 3; ++a) {
  
			string A = s.substr(0, a);
            if (a > 1 && A[0] == '0') continue;
			for (b = 1; b < 4 && a + b <= s.size() - 2; ++b) {
				string B = s.substr(0 + a, b);
                if (b > 1 && B[0] == '0') continue;
				for (c = 1; c < 4 && a + b + c <= s.size() - 1; ++c) {
					string C = s.substr(0 + a + b, c);
                    if (c > 1 && C[0] == '0') continue;
					for (d = 1; d < 4 && a + b + c + d <= s.size(); ++d) {
						string D = s.substr(0 + a + b + c, d);
                        if (d > 1 && D[0] == '0') continue;
						if (A.size() + B.size() + C.size() + D.size() == s.size() && stoi(A) <= 255 && stoi(B) <= 255 && stoi(C) <= 255 && stoi(D) <= 255) {
							results.push_back(A + "." + B + "." + C + "." + D);
						}
					}
				}
			}
		}
		return results;
	}
};
