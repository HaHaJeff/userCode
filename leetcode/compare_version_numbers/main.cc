class Solution {
public:
	int compareVersion(string version1, string version2) {
		int s1 = version1.size();
		int s2 = version2.size();

		int i = 0, j = 0;
		while (i < s1 || j < s2) {

			int num1 = 0, num2 = 0;
			while (i < s1 && version1[i] != '.') {
				num1 = (version1[i] - '0' + num1 * 10);
				i++;
			}

			while (j < s2 && version2[j] != '.') {
				num2 = (version2[j] - '0' + num2 * 10);
				j++;
			}

			if (num1 < num2) return -1;
			if (num1 > num2) return 1;

			i++;
			j++;
		}

		return 0;
	}
};

