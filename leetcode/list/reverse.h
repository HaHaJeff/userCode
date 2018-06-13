#include "list.h"

class Solution {
  public:
    struct Node *Reverse(struct Node *head, int from, int to) {

      struct Node *node = head;
      struct Node *front = NULL;
      struct Node *tail = NULL;
      int len = 0;

      while (node != NULL) {
        len++;
        front = len == from - 1 ? node : front;
        tail = len == to + 1 ? node : tail;
        node = node->next;
      }
      if (from > to || from < 1 || to > len) return NULL;

      node = front == NULL ? head : front->next;
      struct Node *node1 = node->next;
      struct Node *node2 = NULL;

      node->next = tail;

      while (node1 != tail) {
        node2 = node1->next;
        node1->next = node;
        node = node1;
        node1 = node2;
      }

      if (front!= NULL) {
        front->next = node;
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

      list.head = Reverse(list.head, 2, 3);

      list.Print();
    }
};
