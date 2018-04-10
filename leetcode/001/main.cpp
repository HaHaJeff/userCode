#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        static bool myfun(const pair<int, int> a, const pair<int, int> b)
        {
            if(a.first * b.first >= 0)
                return abs(a.first) < abs(b.first);
            else
                return a.first < b.first;
        }

        vector< pair<int, int> > storgeIndex(vector<int> &nums, int target) {

            vector< pair<int, int> > index;

            int length = nums.size();

            for(int i = 0; i < length; i++) {
                index.push_back(pair<int, int>(nums[i], i));
            }

            return index;
        }

        vector<int> twoSum(vector<int>& nums, int target) {

            vector< pair<int, int> > index(storgeIndex(nums, target));

            sort(index.begin(), index.end(), myfun);

            int length = nums.size();

            int i = 0;

            int j = length - 1;

            vector<int> ret;

            for(i = 0; i < j; ) {

                if(abs(index[i].first + index[j].first) > abs(target)) --j;

                if(abs(index[i].first + index[j].first) < abs(target)) ++i;

                if(abs(index[i].first + index[j].first) == abs(target)) break;
            }

            if(i < length && j >= 0 && i < j) {
                ret.push_back(index[i].second);
                ret.push_back(index[j].second);
            }

            return ret;

        }
};

/*hash 方法更加迅速*/

/*
int main(void)
{
    int arr[] = {-1,-2,-3,-4,-5};

    int length = sizeof(arr)/sizeof(int);

    vector<int> nums(arr, arr + length);

    Solution sol;

    vector<int> ret = sol.twoSum(nums, -8);

    cout << "[" << ret[0] << "," << ret[1] << "]" << endl;

    return 0;
}
*/
