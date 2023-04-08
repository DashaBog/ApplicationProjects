#include <iostream>
#include <string>

void Push(int n, int* arr, int* top, int* minim) {
  if (*top == -1) {
    minim[0] = n;
  } else {
    minim[*top + 1] = std::min(n, minim[*top]);
  }
  (*top)++;
  arr[*top] = n;
  std::cout << "ok\n";
}

void Pop(int const* arr, int* top) {
  if (*top == -1) {
    std::cout << "error\n";
  } else {
    std::cout << arr[*top] << "\n";
    *top = *top - 1;
  }
}

void Back(int const* arr, int const* top) {
  if (*top == -1) {
    std::cout << "error\n";
  } else {
    std::cout << arr[*top] << "\n";
  }
}

int Size(int const* top) { return *top + 1; }

void Clear(int* top) {
  *top = -1;
  std::cout << "ok\n";
}

void Min(int const* top, int const* minim) {
  if (*top == -1) {
    std::cout << "error\n";
  } else {
    std::cout << minim[*top] << "\n";
  }
}

void Cinx(std::string s, int n, int* arr, int* top, int* minim) {
  for (int i = 0; i < n; i++) {
    std::cin >> s;
    if (s == "pop") {
      Pop(arr, top);
    } else if (s == "back") {
      Back(arr, top);
    } else if (s == "clear") {
      Clear(top);
    } else if (s == "min") {
      Min(top, minim);
    } else if (s == "size") {
      std::cout << Size(top) << std::endl;
    } else {
      int k;
      std::cin >> k;
      Push(k, arr, top, minim);
    }
  }
}

int main() {
  int* arr = new int[200000];
  int* minim = new int[200000];
  int top = -1;
  int n;
  std::cin >> n;
  std::string s;
  Cinx(s, n, arr, &top, minim);
  delete[] arr;
  delete[] minim;
  return 0;
}