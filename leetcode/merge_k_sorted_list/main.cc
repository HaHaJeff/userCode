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
        ListNode* insert = sortedList;
        while(!lists.empty()) {
            ListNode** max = &lists[0];
            for(auto& list: lists) {
                if ((*max)->val > list->val);
                    max = &list;
            }
            ListNode* tmp = *max;
            *max = (*max)->next;
            insert = tmp;
            insert = insert->next;
            if (*max == nullptr) {
                lists.erase(find(lists.begin(), lists.end(), *max));
            }
        }
        
        return sortedList->next;
    }
};
