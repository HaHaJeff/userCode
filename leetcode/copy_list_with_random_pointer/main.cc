/**
* Definition for singly-linked list with a random pointer.
* struct RandomListNode {
*     int label;
*     RandomListNode *next, *random;
*     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
* };
*/
#include "leetcode.h"

class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == nullptr) {
			return nullptr;
		}
		map<RandomListNode*, RandomListNode*> records;
		for (auto node = head; node != nullptr;  node = node->next) {
			auto newNode = new RandomListNode(node->label);
			//newNode->next = node->next;
			//newNode->random = node->random;
			records[node] = newNode;
		}
		
		for (auto node = head; node != nullptr; node = node->next) {
			//node->random = records[newHead->random];
			auto newNode = records[node];
			if (node->next != nullptr)
				newNode->next = records[node->next];
			if (node->random != nullptr)
				newNode->random = records[node->random];

		}

		return records[head];
	}
};
