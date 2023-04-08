#include <algorithm>
#include <iostream>

struct Item {
  int key;
  int prior;
  int num;
  Item* left;
  Item* right;
  Item* parent;
  Item(int key, int prior, int num)
      : key(key),
        prior(prior),
        num(num),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
};

Item* tree;

void BuildTree(int* parent, int* leftchild, int* rightchild, Item* array) {
  if (tree == nullptr) {
    tree = array;
  } else if (tree->prior < array->prior) {
    tree->right = array;
    rightchild[tree->num] = array->num;
    array->parent = tree;
    parent[array->num] = tree->num;
    tree = array;
  } else {
    while (tree->prior > array->prior && tree->parent != NULL) {
      tree = tree->parent;
    }
    if (tree->parent == NULL && tree->prior > array->prior) {
      array->left = tree;
      leftchild[array->num] = tree->num;
      tree->parent = array;
      parent[tree->num] = array->num;
      tree = array;
    } else {
      array->left = tree->right;
      leftchild[array->num] = tree->right->num;
      tree->right->parent = array;
      parent[tree->right->num] = array->num;
      tree->right = array;
      rightchild[tree->num] = array->num;
      array->parent = tree;
      parent[array->num] = tree->num;
      tree = array;
    }
  }
}

void Print(int num, int* parent, int* leftchild, int* rightchild) {
  std::cout << "YES\n";
  for (int i = 1; i <= num; i++) {
    std::cout << parent[i];
    std::cout << " " << leftchild[i] << " " << rightchild[i] << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int* parent = new int[51000];
  int* leftchild = new int[51000];
  int* rightchild = new int[51000];
  int num;
  std::cin >> num;
  for (int i = 0; i < num + 1; i++) {
    parent[i] = 0;
    leftchild[i] = 0;
    rightchild[i] = 0;
  }
  for (int i = 0; i < num; i++) {
    int key, prior;
    std::cin >> key >> prior;
    Item* array = new Item(key, prior, i + 1);
    BuildTree(parent, leftchild, rightchild, array);
  }
  Print(num, parent, leftchild, rightchild);
  delete[] parent;
  delete[] leftchild;
  delete[] rightchild;
}