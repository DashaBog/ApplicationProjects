#include <iostream>

void Push(int n, int* arr, int* top) {
  (*top)++;
  arr[*top] = n;
}

int Pop(const int* arr, int* top) {
  *top = *top - 1;
  return arr[*top + 1];
}

bool Balanced(int* arr, int* top) {
  std::string vv;
  std::getline(std::cin, vv);
  for (int i = 0; i < (int)vv.length(); ++i) {
    if (vv[i] == '(') {
      Push(')', arr, top);
    } else if (vv[i] == '[') {
      Push(']', arr, top);
    } else if (vv[i] == '{') {
      Push('}', arr, top);
    } else if (*top != -1 && vv[i] == Pop(arr, top)) {
      continue;
    } else {
      *top = 1;
      break;
    }
  }
  return *top == -1;
}

int main() {
  int* arr = new int[200000];
  int top = -1;
  if (Balanced(arr, &top)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[](arr);
  return 0;
}