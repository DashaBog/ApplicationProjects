#include <iostream>
#include <string>

//СТЕК

bool Empty(int const* top) { return (*top == -1); }

int Size(int const* top) { return *top + 1; }

void Push(int n, int* arr, int* top, int* minim) {
  if (*top == -1) {
    minim[0] = n;
  } else {
    minim[*top + 1] = std::min(n, minim[*top]);
  }
  (*top)++;
  arr[*top] = n;
  for (int i = 0; i < Size(top); ++i) {std::cout << arr[i] << "_";}
}

void Pop(int* top) {
  if (*top != -1) {
    *top = *top - 1;
  }
}

int Back(int const* arr, int const* top) {
  for (int i = 0; i < Size(top); ++i) {std::cout << arr[i] << "_";}
  return (*top != -1) ? arr[*top] : -1;
}

void Clear(int* top) { *top = -1; }

void Min(int const* top, int const* minim) {
  if (*top == -1) {
    std::cout << "error\n";
  } else {
    std::cout << minim[*top] << "\n";
  }
}

//ОЧЕРЕДЬ

void Enqueue(int k, int* arr1, int* front, int* minim1) {
  Push(k, arr1, front, minim1);
  std::cout << "ok\n";
}

void Dequeue(int* arr1, int* arr2, int* front, int* rare, int* minim2) {
  if (Empty(rare)) {
    while (!Empty(front)) {
      int element = Back(arr1, front);
      Pop(front);
      Push(element, arr2, rare, minim2);
    }
  }
  int result = Back(arr2, rare);
  Pop(rare);
  if (result == -1) {
    std::cout << "error\n";
  } else {
    std::cout << result << "\n";
  }
}

void Front(int* arr1, int* arr2, int* front, int* rare, int* minim2) {
  if (*front == -1 && *rare == -1) {
    std::cout << "error\n";
    return;
  }
  if (Empty(rare)) {
    while (!Empty(front)) {
      int element = Back(arr1, front);
      Pop(front);
      Push(element, arr2, rare, minim2);
    }
  }
  int result = Back(arr2, rare);
  std::cout << result << "\n";
}

int Size(int* front, int* rare) { return Size(rare) + Size(front); }

void Clear(int* front, int* rare) {
  Clear(front);
  Clear(rare);
  std::cout << "ok\n";
}

void Min(int* front, int* rare, int* minim1, int* minim2) {
  if (*front == -1 && *rare == -1) {
    std::cout << "error\n";
    return;
  }
  int currmin = 0;
  if (Empty(front) || Empty(rare)) {
    if (Empty(front)) {
      currmin = Back(minim2, rare);
    } else {
      currmin = Back(minim1, front);
    }
    // currmin = Empty(front) ? Back(minim2, rare) : Back(minim1, front);
  } else {
    currmin = std::min(Back(minim1, front), Back(minim2, rare));
  }
  std::cout << currmin << "\n";
}

void Cinx(int* arr1, int* arr2, int* minim1, int* minim2) {
  int front = -1;
  int rare = -1;
  int n;
  std::cin >> n;
  std::string s;
  for (int i = 0; i < n; i++) {
    std::cin >> s;
    if (s == "dequeue") {
      Dequeue(arr1, arr2, &front, &rare, minim2);
    } else if (s == "front") {
      Front(arr1, arr2, &front, &rare, minim2);
    } else if (s == "clear") {
      Clear(&front, &rare);
    } else if (s == "min") {
      Min(&front, &rare, minim1, minim2);
    } else if (s == "size") {
      std::cout << Size(&front, &rare) << "\n";
    } else {
      int k;
      std::cin >> k;
      Enqueue(k, arr1, &front, minim1);
    }
  }
}

int main() {
  int* arr1 = new int[200001];
  int* minim1 = new int[200001];
  int* arr2 = new int[200001];
  int* minim2 = new int[200001];
  Cinx(arr1, arr2, minim1, minim2);
  delete[] arr1;
  delete[] arr2;
  delete[] minim1;
  delete[] minim2;
  return 0;
}

/*#include <iostream>
#include <string>

class Stack {
  static const int kSize = 200001;
  int* arr_;
  int* minim_;
  int top_;

 public:
  Stack() {
    arr_ = new int[kSize];
    minim_ = new int[kSize];
    top_ = -1;
  }
  ~Stack() {
    delete[] arr_;
    delete[] minim_;
  }
  bool Empty() const { return (top_ == -1); }
  int GetTop() const { return top_; }
  void SetTop(int value) { top_ = value; }
  void Push(int value) {
    if (top_ == -1) {
      minim_[0] = value;
    } else {
      minim_[top_ + 1] = std::min(value, minim_[top_]);
    }
    (top_)++;
    arr_[top_] = value;
  }
  void Pop() {
    if (top_ != -1) {
      top_ = top_ - 1;
    }
  }
  int Back() {
    return (top_ != -1) ? arr_[top_] : -1;
  }
  int Size() const { return top_ + 1; }
  void Clear() { top_ = -1; }
  void Min() {
    if (top_ == -1) {
      std::cout << "error\n";
    } else {
      std::cout << minim_[top_] << "\n";
    }
  }
};

class Deque {
  friend class Stack;
  Stack front_;
  Stack rare_;

 public:
  Deque() = default;
  ~Deque() = default;
  void Enqueue(int value) {
    front_.Push(value);
    std::cout << "ok\n";
  }
  void Dequeue() {
    if (rare_.Empty()) {
      while (!front_.Empty()) {
        int element = front_.Back();
        front_.Pop();
        rare_.Push(element);
      }
    }
    int result = rare_.Back();
    rare_.Pop();
    if (result == -1) {
      std::cout << "error\n";
    } else {
      std::cout << result << "\n";
    }
  }
  void Front() {
    if (front_.GetTop() == -1 && rare_.GetTop() == -1) {
      std::cout << "error\n";
      return;
    }
    if (rare_.Empty()) {
      while (!front_.Empty()) {
        int element = front_.Back();
        front_.Pop();
        rare_.Push(element);
      }
    }
    int result = rare_.Back();
    std::cout << result << "\n";
  }
  int Size() { return rare_.Size() + front_.Size(); }
  void Clear() {
    front_.Clear();
    rare_.Clear();
    std::cout << "ok\n";
  }
  void Min() {
    if (front_.GetTop() == -1 && rare_.GetTop() == -1) {
      std::cout << "error\n";
      return;
    }
    int currmin = 0;
    if (front_.Empty() || rare_.Empty()) {
      if (front_.Empty()) {
        currmin = rare_.Back();
      } else {
        currmin = front_.Back();
      }
      // currmin = front_.Empty() ? rare_.Back() : front_.Back();
    } else {
      currmin = std::min(front_.Back(), rare_.Back());
    }
    std::cout << currmin << "\n";
  }
};

void Cinx() {
  Deque hat;
  int numreq;
  std::cin >> numreq;
  std::string req;
  for (int i = 0; i < numreq; i++) {
    std::cin >> req;
    if (req == "dequeue") {
      hat.Dequeue();
    } else if (req == "front") {
      hat.Front();
    } else if (req == "clear") {
      hat.Clear();
    } else if (req == "min") {
      hat.Min();
    } else if (req == "size") {
      std::cout << hat.Size() << "\n";
    } else {
      int value;
      std::cin >> value;
      hat.Enqueue(value);
    }
  }
}

int main() {
  Cinx();
  return 0;
}*/