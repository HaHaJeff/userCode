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
	bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;
		ListNode* slow = head, *fast = head;

		while (fast->next != nullptr && fast->next->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}

		slow->next = reverseList(slow->next);
		slow = slow->next;

		while (slow != nullptr) {
			if (head->val != slow->val) return false;
			head = head->next;
			slow = slow->next;
		}

		return true;

	}

	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		ListNode* next = head;

		while (head != nullptr) {
			next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}

		return prev;
	}
};
