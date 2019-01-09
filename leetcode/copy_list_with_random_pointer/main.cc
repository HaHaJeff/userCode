/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:

	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == nullptr) {
			return nullptr;
		}

		//利用node的next字段保存当前node的copy
		//利用copy的next字段保存当前node的next
		for (auto node = head; node != nullptr;) {
			auto newNode = new RandomListNode(node->label);
			auto next = node->next;
			node->next = newNode;
			newNode->next = next;
			node = next;
		}

		//改变newNode的random字段
		for (auto node = head; node != nullptr;) {
			auto next = node->next->next;

			if (node->random != nullptr) {
				node->next->random = node->random->next;
			}
			node = next;
		}

		RandomListNode* newHead = new RandomListNode(0);
		RandomListNode* newNode = newHead;
		for (auto node = head; node != nullptr;) {
			
			auto next = node->next->next;
			newNode->next = node->next;
			newNode = node->next;
            node->next = next;
			node = next;
		}
		return newHead->next;
	}
};
