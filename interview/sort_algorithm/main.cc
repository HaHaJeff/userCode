#include "quick_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"

int main()
{
    vector<int> nums = {8,4,2,3,1,5,8,6};
    HeapSort(nums);
    auto func = [=](){for (auto& num : nums) std::cout << num <<" "; std::cout << std::endl;};
    func();

}
