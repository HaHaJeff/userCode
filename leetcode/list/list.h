#include <iostream>

#ifndef __LIST_H__
#define __LIST_H__


struct Node {
  Node (int v) : next(NULL), val(v) {  }
  struct Node *next;
  int val;
};

class List {
  public:

    List() : head(NULL){  }

    struct Node *GetTail() {
      struct Node *tmp = head;
      while (tmp != NULL && tmp->next != NULL) tmp = tmp->next;
      return tmp;
    }

    void PushBack(int val) {
      struct Node *node = new struct Node(val);
      struct Node *tail = GetTail();
      if (tail == NULL) head = node;
      else tail->next = node;
    }

    void Print() {
      struct Node *tmp = head;
      while (tmp != NULL) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
      }
      std::cout << std::endl;
    }

    ~List() {
      struct Node *tmp = head;

      while (tmp != NULL) {
        delete(tmp);
        tmp = tmp->next;
      }
    }

    struct Node *head;
};

#endif
