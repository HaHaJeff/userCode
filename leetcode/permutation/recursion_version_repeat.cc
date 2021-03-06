#include <iostream>

bool CanSwap(char *arr, int start, int end);

void Print(char *arr, int len);

void Swap(char *arr, int i, int j);

void Permutation(char *arr, int start, int end);

int main()
{
  char arr[] = "1223";
  int size = sizeof(arr)/sizeof(char);
  Permutation(arr, 0, size-2);
}

bool CanSwap(char *arr, int start, int end)
{
  bool canSwap = true;

  for (int i = start; i < end; i++) {
    if (arr[i] == arr[end]) {
      canSwap = false;
      break;
    }
  }

  return canSwap;
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

void Swap(char *arr, int i, int j)
{
  char temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void Permutation(char *arr, int start, int end)
{
  if (start == end) {
    Print(arr, end + 1);
    return;
  }


  for (int i = start; i <= end; i++) {

    if (CanSwap(arr, start, i) == false) {
      continue;
    }

    Swap(arr, start, i);
    Permutation(arr, start+1, end);
    Swap(arr, start, i);
  }
}
