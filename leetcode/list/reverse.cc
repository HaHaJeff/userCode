#include "list.h"

class Solution {
  public:
    struct Node *Reverse(struct Node *head, int from, int to) {


      struct Node *node = head;
      struct Node *pre = NULL;
      struct Node *last = NULL;
      int len = 0;

      while (node != NULL) {
        len++;
        pre = len == from - 1 ? node : pre;
        last = len == to + 1 ? node : last;
      }
      if (from > to || from < 1 || to > len) return NULL;

      node = pre == NULL ? head : pre->next;
      struct Node *node1 = node->next;
      struct Node *next = NULL;

      while (node1 != last) {
        next = node1->next;
        node1->next = node;
        node = node1;
        node1 = next;
      }

      if (pre != NULL) {
        pre->next = node;
        return head;
      }
      return node;


    }

    struct Node *ReverseList(struct Node *head, int from, int to) {

      struct Node *pre = NULL;
      struct Node *next = NULL;

      while (head != NULL) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
      }

      return pre;

    }

    void Test() {
      List list;
      list.PushBack(1);
      list.PushBack(2);
      list.PushBack(3);
      list.PushBack(4);

      list.head = Reverse(list.head, 1, 4);

      list.Print();
    }
};

int main()
{
  Solution sol;
  sol.Test();
  return 0;
}
