#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void QuickSort(vector<int>& nums) ;
int Partition(vector<int>& nums, int start, int end);
void SortCoreRec(vector<int>& nums, int start, int end);
void SortCoreIter(vector<int>& nums, int start, int end);

void QuickSort(vector<int>& nums) {
    SortCoreIter(nums, 0, nums.size()-1);
}

int Partition(vector<int>& nums, int start, int end) {
    int pivot = nums[start];
    while (start < end) {
        while (pivot <= nums[end] && start < end) --end;
        nums[start] = nums[end];
        while (pivot >= nums[start] && start < end) ++start;
        nums[end] = nums[start];
    }
    nums[start] = pivot;
    return start;
}

void SortCoreRec(vector<int>& nums, int start, int end) {
    if (start < end) {
        int mid = Partition(nums, start, end);
        SortCoreRec(nums, start, mid-1);
        SortCoreRec(nums, mid+1, end);
    }
}

void SortCoreIter(vector<int>& nums, int start, int end) {
    stack<int> s;
    s.push(start);
    s.push(end);

    int l = 0, r = 0, mid = 0;
    while (!s.empty()) {
        r = s.top();s.pop();
        l = s.top();s.pop();
        mid = Partition(nums, l, r);
        if (l < mid) {
            s.push(l);
            s.push(mid-1);
        }
        if (r > mid) {
            s.push(mid+1);
            s.push(r);
        }
    }
}
