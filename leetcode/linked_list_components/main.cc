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
    int numComponents(ListNode* head, vector<int>& G) {
        std::unordered_set<int> g(G.begin(), G.end());
        int res = 0;
        while (head != nullptr) {
            res += g.count(head->val) && (head->next == nullptr || !g.count(head->next->val)) ? 1 : 0;
            head = head->next;
        }
        
        return res;
    }
};
