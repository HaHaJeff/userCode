/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *attach(ListNode* l1, ListNode *l2, int cd) {
        ListNode *p1End = l1;
        for(; p1End->next != NULL; p1End = p1End->next) ;
        int tmp = 0;
        /*直接连接*/
        p1End->next = l2;
        /*如果有进位，则再行计算*/
        if(cd >= 1) {
            ListNode *p2;
            for(p2 = l2; p2->next != NULL; p2 = p2->next) {
                tmp = cd + p2->val;
                p2->val = tmp % 10;
                if(tmp >= 10) cd = tmp % 9;
                else cd = 0;
            }
            if(cd == 1) {
                tmp = cd + p2->val;
                p2->val = tmp % 10;
                if(tmp >= 10) cd = tmp % 9;
                else cd = 0;
                /*如果cd=0，则直接退出，否则需要创建一个节点，值为cd，并进行连接操作*/
                if(cd == 0) ;
                else {
                    ListNode *pTmp = new ListNode(cd);
                    p2->next = pTmp;
                }
            }
        }
        return l1;

    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        ListNode *p1 = l1, *p2 = l2;
        ListNode *pHead = NULL, *pTmp = NULL;
        ListNode *p1Begin = l1, *p2Begin = l2;
        int tmp = 0;
        /*carry digit　进位*/
        int cd = 0;
        while(p1 != NULL && p2 != NULL) {
            tmp = p1->val + p2->val + cd;
            ListNode *pNode = new ListNode(tmp % 10);

            if(pHead == NULL) {
                pHead = pNode;
                pTmp = pHead;
            } else {
                pTmp->next = pNode;
                pTmp = pNode;
            }
            if(tmp >= 10)
                cd  = tmp / 10;
            else cd = 0;

            p1 = p1->next;
            p2 = p2->next;
        }
        if(p1 != NULL && p2 == NULL) {
           attach(pHead, p1, cd);
        }
        if(p2 != NULL && p1 == NULL) {
            attach(pHead, p2, cd);
        }
        if(p1 == NULL && p2 == NULL && cd >= 1) {
            ListNode *pNode = new ListNode(cd % 10); 
            pTmp->next = pNode;
            pTmp = pNode;            
        }
        return pHead;
    }
};

#if 0
int main(void)
{
    ListNode p1(2), p2(4), p3(3) ,p4(5), l1(5), l2(6), l3(4);
    p1.next = &p2;
    p2.next = &p3;
    p3.next = &p4;

    l1.next = &l2;
    l2.next = &l3;
    Solution sol;
    ListNode *pRet = sol.addTwoNumbers(&p1, &l1);
    for(; pRet != NULL; pRet = pRet->next) cout << pRet->val << " ";
    cout << endl;
    return 0;
}
#endif

#if 1

int main(void) {
    ListNode p1(1), p2(8), l1(0);
    p1.next = &p2;
    Solution sol;

    ListNode *pRet = sol.addTwoNumbers(&p1, &l1);
    for(; pRet != NULL; pRet = pRet->next) cout << pRet->val << " ";
    cout << endl;
    return 0;
}
#endif
