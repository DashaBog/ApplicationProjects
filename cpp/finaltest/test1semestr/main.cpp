#include <iostream>

int& f(int x) {
//  return x * x;
}
int main() {
  int a = 1;
  int b = 2;
  int c = 0;
  if (a > 1)
    if (b > 1) c = 5;
    else
      c = 6;
  std::cout << c;
//  std::cout << f(5);
}
