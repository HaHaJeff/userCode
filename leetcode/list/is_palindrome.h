#include "reverse.h"

bool IsPalindrom(struct Node *head) {
  struct Node *node = head;
  struct Node *mid = head;

  //Get mid node;
  while (node->next != NULL && node->next->next != NULL) {
    mid = mid->next;
    node = node->next;
  }

  node = mid->next;
  struct Node *next = NULL;
  struct Node *pre = NULL;

  mid->next = NULL;

  while (node != NULL) {
    next = node->next;
    node->next = pre;
    pre = node;
    node = next;
  }

  struct Node *rightStart = pre;
  struct Node *leftStart = head;

  while (leftStart != NULL && rightStart != NULL) {
    if (leftStart->val !=rightStart->val) {
      return false;
    }
    leftStart  = leftStart->next;
    rightStart = rightStart->next;
  }

  next = NULL;
  node = pre;
  pre = NULL;

  while (node != NULL) {
    next = node->next;
    node->next = pre;
    pre = node;
    node = next;
  }

  mid->next = pre;
  return true;

}

/*
int main()
{
  List list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(2);
  list.PushBack(1);

  std::cout << IsPalindrom(list.head) << std::endl;

  list.Print();

  return 0;
}
*/
