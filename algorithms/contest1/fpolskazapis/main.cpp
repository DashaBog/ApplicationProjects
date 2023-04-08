#include <cctype>
#include <iostream>

void Push(int n, int* arr, int* top) {
  (*top)++;
  arr[*top] = n;
}

int Pop(int const* arr, int* top) {
  if (*top != -1) {
    *top = *top - 1;
  }
  return arr[*top + 1];
}

int Execute(char op, int first, int second) {
  switch (op) {
    case '+':
      return (first + second);
      break;
    case '-':
      return (first - second);
      break;
    case '*':
      return (first * second);
      break;
    default:
      return 0;
  }
}

int Calculation(std::string s, int* arr, int* top) {
  int result = 0;
  for (int i = 0; i < (int)s.length(); ++i) {
    if (0 < isdigit(s[i])) {
      int c = (int)s[i] - '0';
      Push(c, arr, top);
    } else if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
      int second = Pop(arr, top);
      int first = Pop(arr, top);
      result = Execute(s[i], first, second);
      Push(result, arr, top);
    }
  }
  return result;
}

int main() {
  std::string s;
  std::getline(std::cin, s);
  int* arr = new int[200000];
  int top = -1;
  std::cout << Calculation(s, arr, &top);
  delete[](arr);
  return 0;
}