#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
class Solution {
  public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
      vector<vector<int>> ret;
      int size = nums.size();
      int first = 0, second = 1, third = 2, four = size - 1;
      int current = target;
      sort(nums.begin(), nums.end());
      for (; first < size - 3 ; first++) {
        current -= nums[first];
        for (second = first + 1; second < size - 2; second++) {
          current -= nums[second];
          third = second + 1;
          four = size - 1;
          while(third < four) {
            if (nums[third] + nums[four] < current) third++;
            else if (nums[third] + nums[four] > current) four--;
            else {
              ret.push_back({nums[first], nums[second], nums[third], nums[four]});
              four--;
              //third++;
              while (four <= size - 1 && nums[four] == nums[four+1]) four--;
              while (third <= four && nums[third] == nums[third+1]) third++;
            }
          }
          current += nums[second];
          while (second <= third && nums[second] == nums[second+1]) second++;
        }
        current += nums[first];
        while (first <= second && nums[first] == nums[first+1]) first++;
      }

      return move(ret);
    }
};

int main()
{
  vector<int> nums = {-5, -4, -2, -2, -2, -1, 0, 0, 1};
  int target = -9;
  Solution sol;
  auto ret = sol.fourSum(nums, target);

  for_each(ret.begin(), ret.end(), [](auto& item){
      for_each(item.begin(), item.end(), [](auto& i){
          std::cout << i << ' ';
          });
      std::cout << std::endl;
      });
}
