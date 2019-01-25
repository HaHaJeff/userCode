/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class SolutionForce {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* intersection = nullptr;
        ListNode* nodeA = headA;
        ListNode* nodeB = headB;
        
        while (nodeA != nullptr) {
            while (nodeB != nullptr && nodeA != nodeB) {
                nodeB = nodeB->next;
            }
            if (nodeA == nodeB) {
                intersection = nodeA;
                break;
            }
            nodeA = nodeA->next;
            nodeB = headB;
        }

        if (nodeA == nullptr) intersection = nodeA;
        return intersection;
    }
};

class Solution1 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* intersection = nullptr;
        ListNode* nodeA = headA;
        ListNode* nodeB = headB;
        
        int lenA = 0, lenB = 0;
        
        while (nodeA != nullptr) {
            lenA++;
            nodeA = nodeA->next;
        }
        while (nodeB != nullptr) {
            lenB++;
            nodeB = nodeB->next;
        }
        nodeA = headA;
        nodeB = headB;

        if (lenA < lenB) {

            for(int i = 0; i < lenB-lenA && nodeB != nullptr; i++) {
                nodeB = nodeB->next;
            }
        } else {
            for (int i = 0; i < lenA - lenB && nodeA != nullptr; i++) {
                nodeA = nodeA->next;
            }
        }
        
        while(nodeA != nullptr && nodeB != nullptr && nodeA != nodeB) {
            nodeA = nodeA->next;
            nodeB = nodeB->next;
        }
        intersection = nodeA;
        return intersection;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) return nullptr;
        ListNode* nodeA = headA;
        ListNode* nodeB = headB;
        
        while (nodeA != nodeB) {
            nodeA = nodeA == nullptr ? headB : nodeA->next;
            nodeB = nodeB == nullptr ? headA : nodeB->next;
        }
        
        return nodeA;
    }
};
