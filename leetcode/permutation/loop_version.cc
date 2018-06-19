#include <iostream>

void Print(char *arr, int len);

void Swap(char *p, char *q);

void Permutation(char *arr, int start, int end);

void Reverse(char *pStart, char *pEnd);

bool NextPermutation(char *arr, int len);

int main()
{
  char arr[] = "1223";
  int size = sizeof(arr)/sizeof(char);
  Permutation(arr, 0, size-2);
}

void Print(char *arr, int len)
{
  static int nCount = 0;
  nCount++;
  std::cout << nCount << ":" << "\t";
  for (int i = 0; i < len; i++) {
    std::cout << arr[i];
  }
  std::cout << std::endl;
}

void Swap(char *p, char *q)
{
  char temp = *p;
  *p = *q;
  *q = temp;
}

bool NextPermutation(char *arr, int len)
{
  char *pEnd = arr + len;
  char *pStart = arr;
  char *p, *q;
  char *pFind = NULL;
  p = --pEnd;

  while (p != pStart) {
    q = p;
    p--;

    //找到合适相邻两个数
    if (*p < *q) {
      pFind = pEnd;
        //从后往前找到第一个比p大的数；
        while (*pFind <= *p) {
          pFind--;
        }
      Swap(pFind, p);
      Reverse(q, pEnd);
      return true;
    }
  }
  return false;
}

void Reverse(char *pStart, char *pEnd)
{
  while (pStart < pEnd) {
    Swap(pStart++, pEnd--);
  }
}

void Permutation(char *arr, int start, int end)
{
  Print(arr, end + 1);
  while (NextPermutation(arr, end + 1)) {
    Print(arr, end + 1);
  }
}
