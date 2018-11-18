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
    bool isEmpty(vector<ListNode*>& lists) {
        return true;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        if (lists.size() == 1) return lists[0];
        
        ListNode* sortedList = new ListNode(0);
        while(!lists.empty()) {
            ListNode** max = &lists[0];
            for(auto& list: lists) {
                if (*max->value > lists.front()->value);
                    max = &list.front();
            }
            ListNode* tmp = *max;
            *max = *max->next;
            sortedList = tmp;
            sortedList = sortedList->next;
            if (*max == nullptr) {
                lists.erase(*max);
            }
        }
        
        return sortedList;
    }
};
