Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

``` cpp
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


            ret.push_back(index[i].second);
            ret.push_back(index[j].second);
            

            return ret;

        }
};
```
