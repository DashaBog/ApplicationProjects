#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>

struct Item {
  int key;
  int prior;
  int size;
  Item* left;
  Item* right;
  Item(int key, int prior)
      : key(key), prior(prior), size(0), left(nullptr), right(nullptr) {}
  ~Item() {
    delete left;
    delete right;
  }
};
typedef Item* PItem;

const int kError = INT_MIN;

int GetSize(PItem t) {
  if (t == nullptr) {
    return 0;
  }
  return t->size;
}

PItem Update(PItem t) {
  if (t == nullptr) {
    return t;
  }
  t->size = GetSize(t->left) + GetSize(t->right) + 1;
  return t;
}

PItem Merge(PItem l, PItem r) {
  if (l == nullptr) {
    return r;
  }
  if (r == nullptr) {
    return l;
  }
  if (l->prior > r->prior) {
    l->right = Merge(l->right, r);
    l = Update(l);
    return l;
  }

  r->left = Merge(l, r->left);
  r = Update(r);
  return r;
}

void Split(PItem t, int num, PItem& l, PItem& r) {
  if (t == nullptr) {
    l = nullptr;
    r = nullptr;
  } else if (t->key <= num) {
    Split(t->right, num, t->right, r);
    l = t;
  } else {
    Split(t->left, num, l, t->left);
    r = t;
  }
}

bool Exists(PItem t, int key) {
  if (t == nullptr) {
    return false;
  }
  if (t->key == key) {
    return true;
  }
  if (t->left != nullptr && key < t->key) {
    return Exists(t->left, key);
  }
  if (t->right != nullptr && key > t->key) {
    return Exists(t->right, key);
  }
  return false;
}

void Insert(PItem& t, int key, int prior) {
  if (t == nullptr) {
    t = new Item(key, prior);
    return;
  }
  if (Exists(t, key)) {
    return;
  }
  PItem l, r;
  Split(t, key, l, r);
  PItem v = new Item(key, prior);
  v = Update(v);
  t = Merge(l, Merge(v, r));
  t = Update(t);
}

void Delete(PItem& t, int x) {
  if (!Exists(t, x)) {
    return;
  }
  PItem l1, r1;
  Split(t, x - 1, l1, r1);
  l1 = Update(l1);
  r1 = Update(r1);
  PItem l2, r2;
  Split(r1, x, l2, r2);
  l2 = Update(l2);
  r2 = Update(r2);
  delete l2;
  t = Merge(l1, r2);
  t = Update(t);
}

int Next(PItem t, int x) {
  if (t == nullptr) {
    return x;
  }
  while (t->right != nullptr && t->key < x) {
    t = t->right;
  }
  while (t->left != nullptr && t->left->key > x) {
    t = t->left;
  }
  if (t->key <= x) {
    std::cout << "none" << std::endl;
  } else {
    std::cout << t->key << std::endl;
  }
  return t->key;
}

int Prev(PItem t, int x) {
  if (t == nullptr) {
    return x;
  }
  while (t->left != nullptr && t->key > x) {
    t = t->left;
  }
  while (t->right != nullptr && t->right->key < x) {
    t = t->right;
  }
  if (t->key >= x) {
    std::cout << "none" << std::endl;
  } else {
    std::cout << t->key << std::endl;
  }
  return t->key;
}

int Kth(PItem tree, int x) {
  if (GetSize(tree->left) + 1 == x) {
    return tree->key;
  }
  if (GetSize(tree->left) >= x) {
    if (tree->left == nullptr) {
      return kError;
    }
    return Kth(tree->left, x);
  }
  if (GetSize(tree->left) < x) {
    if (tree->right == nullptr) {
      return kError;
    }
    return Kth(tree->right, x - GetSize(tree->left) - 1);
  }
  return kError;
}

PItem Processing(PItem tree, int x, std::string s) {
  while (std::cin >> s) {
    std::cin >> x;
    if (s == "insert") {
      Insert(tree, x, rand() % 10000);
    } else if (s == "delete") {
      Delete(tree, x);
    } else if (s == "exists") {
      if (Exists(tree, x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (s == "next") {
      Next(tree, x);
    } else if (s == "prev") {
      Prev(tree, x);
    } else if (s == "kth") {
      int tmp = Kth(tree, x);
      if (tmp == kError) {
        std::cout << "none\n";
      } else {
        std::cout << tmp << std::endl;
      }
    }
    tree = Update(tree);
  }
  return tree;
}

int main() {
  int x = 0;
  PItem tree = nullptr;
  std::string s;
  tree = Processing(tree, x, s);
  delete tree;
  return 0;
}