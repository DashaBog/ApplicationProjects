#include <climits>
#include <iostream>
#include <vector>

struct Treap {
  long long key;
  long long prior;
  long long height;
  Treap* left;
  Treap* right;
  Treap(long long key, long long prior)
      : key(key), prior(prior), height(0), left(NULL), right(NULL) {}
};

long long GetHeignt(Treap*& tree) {
  if (tree != nullptr) {
    return tree->height;
  }
  return 0;
}

void UpdateHeight(Treap*& tree) {
  if (tree != nullptr) {
    tree->height = GetHeignt(tree->left) + GetHeignt(tree->right) + tree->key;
  }
}

void Merge(Treap*& tree, Treap* tree_left, Treap* tree_right) {
  if (tree_left == nullptr) {
    tree = tree_right;
    free(tree_left);
  } else if (tree_right == nullptr) {
    tree = tree_left;
  } else if (tree_left->prior <= tree_right->prior) {
    Merge(tree_right->left, tree_left, tree_right->left);
    tree = tree_right;
  } else {
    Merge(tree_left->right, tree_left->right, tree_right);
    tree = tree_left;
  }
  UpdateHeight(tree);
}

void Split(Treap* tree, long long x, Treap*& tree_left, Treap*& tree_right) {
  if (tree == nullptr) {
    tree_left = nullptr;
    tree_right = nullptr;
  } else if (tree->key <= x) {
    Split(tree->right, x, tree->right, tree_right);
    tree_left = tree;
  } else {
    Split(tree->left, x, tree_left, tree->left);
    tree_right = tree;
  }
  UpdateHeight(tree);
}

void Insert(Treap*& tree, Treap*& newnode) {
  if (tree == nullptr) {
    tree = newnode;
  } else if (newnode->prior <= tree->prior) {
    if (newnode->key < tree->key) {
      Insert(tree->left, newnode);
    } else {
      Insert(tree->right, newnode);
    }
  } else {
    Split(tree, newnode->key, newnode->left, newnode->right);
    tree = newnode;
  }
  UpdateHeight(tree);
}

long long GetSum(Treap* tree, long long left, long long right,
                 long long min_subtree, long long max_subtree) {
  if (tree == nullptr) {
    return 0;
  }
  if (tree->key < left) {
    return GetSum(tree->right, left, right, tree->key, max_subtree);
  }
  if (tree->key > right) {
    return GetSum(tree->left, left, right, min_subtree, tree->key + 1);
  }
  long long sum = tree->key;
  if (min_subtree >= left) {
    sum += GetHeignt(tree->left);
  } else {
    sum += GetSum(tree->left, left, right, min_subtree, tree->key + 1);
  }
  if (max_subtree <= right) {
    sum += GetHeignt(tree->right);
  } else {
    sum += GetSum(tree->right, left, right, tree->key, max_subtree);
  }
  return sum;
}

bool Exists(Treap*& tree, long long x) {
  if (tree == nullptr) {
    return false;
  }
  if (tree->key == x) {
    return true;
  }
  if (x >= tree->key) {
    return Exists(tree->right, x);
  }
  return Exists(tree->left, x);
}

/*void DeleteTree(Treap*& root) {
  if (root != nullptr && root->left != nullptr) {
    DeleteTree(root->left);
    root->left = nullptr;
  }
  if (root != nullptr && root->right != nullptr) {
    DeleteTree(root->right);
    root->right = nullptr;
  }
  delete root;
}*/

void DeleteasVector(std::vector<Treap*>& todelete) {
  for (auto c : todelete) {
    delete c;
  }
}

void Processing(Treap* tree, long long n, std::vector<Treap*>& todelete) {
  std::string s;
  char lastpros = '+';
  long long input_first;
  long long input_second;
  long long lastnext = 0;
  for (long long i = 0; i < n; i++) {
    std::cin >> s >> input_first;
    if (s == "+") {
      if (lastpros == '+') {
        if (!Exists(tree, input_first)) {
          Treap* new_el = new Treap(input_first, rand() % 1000000000);
          Insert(tree, new_el);
          todelete.push_back(new_el);
        }
      } else {
        if (!Exists(tree, (input_first + lastnext) % 1000000000)) {
          Treap* new_el = new Treap((input_first + lastnext) % 1000000000,
                                    rand() % 1000000000);
          Insert(tree, new_el);
          todelete.push_back(new_el);
        }
        lastpros = '+';
      }
    } else if (s == "?") {
      std::cin >> input_second;
      lastnext = GetSum(tree, input_first, input_second, 0, LONG_LONG_MAX);
      std::cout << lastnext << "\n";
      lastpros = '?';
    }
  }
  DeleteasVector(todelete);
  // DeleteTree(tree);
}

int main() {
  Treap* tree = nullptr;
  std::vector<Treap*> todelete;
  long long n;
  std::cin >> n;
  Processing(tree, n, todelete);
}