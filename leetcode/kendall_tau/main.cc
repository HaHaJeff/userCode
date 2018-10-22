#include <iostream>
#include <vector>
#include <map>

class KendallTau {
public:
	int GetResult(const std::vector<int>& lhs, const std::vector<int>& rhs) {
		std::map<int, int> index1;
		std::map<int, int> index2;

		for (int i = 0; i < lhs.size(); i++) {
			index1[lhs[i]] = i;
			index2[rhs[i]] = i;
		}

		std::vector<int> index;

		for (int i = 0; i < lhs.size(); i++) {
			index.push_back(index2[lhs[i]]);
		}

		for (auto i : index) {
			std::cout << i << "\t";
		}
		std::cout << "\n";

		int count = 0;
		for (int i = 1; i < index.size(); i++) {
			if (index[i] < index[i - 1]) {
				int j = i;
				int tmp = index[j];
				while (j>0 && index[j-1]>tmp) {
					index[j] = index[j-1];
					count += 1;
					j -= 1;
				}
				index[j] = tmp;
			}
		}

		return count;
	}
};

int main() {
	KendallTau o;
	std::vector<int> lhs = { 0, 3, 1, 6, 2, 5, 4 };
	std::vector<int> rhs = { 1, 0, 3, 6, 4, 2, 5 };
	std::cout << o.GetResult(lhs, rhs) << "\n";
}
