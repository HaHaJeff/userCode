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
        auto cmp = [](auto const* lval, auto const* rval){ return lval->val > rval->val;};
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp); 
        
        for (auto list : lists) {
            if (list != nullptr) pq.push(list);
        }
        
        ListNode* pHead = nullptr;
        ListNode* pNode = pHead;
        
        if (!pq.empty()) {
            pHead = pq.top();  
            pNode = pHead;
            pq.pop();
            if(pNode->next) pq.push(pNode->next);
                    
        }

        while (!pq.empty()) {
            pNode->next = pq.top();
            pNode = pNode->next;
            pq.pop();
            if (pNode->next) pq.push(pNode->next);
        }
        
        return pHead;
        
        /*
        if (lists.empty()) return nullptr;
        if (lists.size() == 1) return lists[0];
        
        ListNode* sortedList = new ListNode(0);
        ListNode* insert = sortedList;
        while(!lists.empty()) {
            ListNode** max = &lists[0];
            for(auto& list: lists) {
                if ((*max)->val < list->val);
                    max = &list;
            }
            ListNode* tmp = *max;
            *max = (*max)->next;
            insert->next = tmp;
            insert = insert->next;
            if (*max == nullptr) {
                lists.erase(find(lists.begin(), lists.end(), *max));
            }
        }
        
        return sortedList->next;
        */

    }
};
