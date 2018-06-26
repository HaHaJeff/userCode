#include <iostream>

inline int GetLeft(int a, int n) {

}

inline int GetRight(int b, int m) {

}

//a*b = (2^n/2 * a_left + a_right)*(2^n/2 * b_left + b_right);
// ==> 2^n*a_left*b_left + a_right*b_right + 2^n/2 * a_left * b_tight
// +2^n/2 * a_rifht * b_left
// a_left*b_right + a_right*b_left = (a_left - a_right)(b_right - b_left)
int Recur(int a, int b, int n, int m) {

  int a_left = GetLeft(a, n);
  int a_right = GetRight(a, n);
  int b_left = GetLeft(b, m);
  int b_right = GetRight(b, m);

}
