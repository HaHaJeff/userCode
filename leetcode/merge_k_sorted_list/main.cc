#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty()) return nullptr;
		if (lists.size() == 1) return lists[0];
		auto begin = lists.begin();
		while (begin != lists.end()) {
			if (*begin == nullptr) {
				lists.erase(begin);
				begin = lists.begin();
			}
			else {
				begin++;
			}
		}

		ListNode* sortedList = new ListNode(0);
		ListNode* insert = sortedList;
		while (!lists.empty()) {
			ListNode** min = &lists[0];
			if (*min != nullptr) {
				for (auto& list : lists) {
					if ((*min)->val > list->val) min = &list;
				}
				insert->next = *min;
				insert = insert->next;
				*min = (*min)->next;
			}

			if (*min == nullptr) {
				lists.erase(find(lists.begin(), lists.end(), *min));
			}
		}

		return sortedList->next;
	}
};
int main()
{
	ListNode list1_1(1);
	ListNode list1_2(4);
	ListNode list1_3(5);
	list1_1.next = &list1_2;
	list1_2.next = &list1_3;

	ListNode list2_1(1);
	ListNode list2_2(3);
	ListNode list2_3(4);
	list2_1.next = &list2_2;
	list2_2.next = &list2_3;

	ListNode list3_1(2);
	ListNode list3_2(6);
	list3_1.next = &list3_2;


	std::vector<ListNode*> lists = { nullptr, &list1_1, &list2_1, &list3_1 };
	Solution sol;
	ListNode* list = sol.mergeKLists(lists);

	while (list != nullptr) {
		std::cout << list->val;
		list = list->next;
	}
}
