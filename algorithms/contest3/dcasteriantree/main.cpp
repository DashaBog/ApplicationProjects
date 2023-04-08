#include <cstdlib>
#include <iostream>
#include <string>

struct Treap {
  long long key;
  long long prior;
  long long height;
  Treap* left;
  Treap* right;
  Treap(long long key, long long prior, long long height)
      : key(key), prior(prior), height(height), left(NULL), right(NULL) {}
};

long long GetHeignt(Treap* tree) {
  if (tree != nullptr) {
    return tree->height;
  }
  return 0;
}

void UpdateHeight(Treap*& tree) {
  if (tree != nullptr) {
    tree->height = GetHeignt(tree->left) + GetHeignt(tree->right) + 1;
  }
}

void Merge(Treap*& tree, Treap* tree_left, Treap* tree_right) {
  if (tree_left == nullptr) {
    tree = tree_right;
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

void Insert(Treap*& tree, Treap* newnode) {
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

void Delete(Treap*& tree, long long x) {
  if (tree->key == x) {
    Treap* deleted = tree;
    Merge(tree, tree->left, tree->right);
    delete deleted;
  } else if (x < tree->key) {
    Delete(tree->left, x);
  } else {
    Delete(tree->right, x);
  }
  UpdateHeight(tree);
}

long long Next(Treap* tree, int x) {
  if (tree == nullptr) {
    return x;
  }
  while (tree->right != nullptr && tree->key < x) {
    tree = tree->right;
  }
  while (tree->left != nullptr && tree->left->key > x) {
    tree = tree->left;
  }
  if (tree->key <= x) {
    return -1;
  }
  return tree->key;
}

long long Prev(Treap* tree, long long x) {
  if (Exists(tree, x)) {
    return x;
  }
  Treap* tree_left = nullptr;
  Treap* tree_right = nullptr;
  Split(tree, x, tree_left, tree_right);
  long long ans;
  if (tree_left == nullptr) {
    Merge(tree, tree_left, tree_right);
    return -1;
  }
  Treap* curr = tree_left;
  while (curr != nullptr && curr->right != nullptr) {
    curr = curr->right;
  }
  ans = curr->key;
  Merge(tree, tree_left, tree_right);
  return ans;
}

long long Kth(Treap* tree, long long x) {
  if (x > GetHeignt(tree)) {
    return -1;
  }
  if (tree == nullptr) {
    return 0;
  }
  long long increased = GetHeignt(tree->left) + 1;
  if (x == increased) {
    return tree->key;
  }
  if (x < increased) {
    return Kth(tree->left, x);
  }
  return Kth(tree->right, x - increased);
}

void DeleteTree(Treap*& root) {
  if (root != nullptr && root->left != nullptr) {
    DeleteTree(root->left);
    root->left = nullptr;
  }
  if (root != nullptr && root->right != nullptr) {
    DeleteTree(root->right);
    root->right = nullptr;
  }
  delete root;
}

void Processing(Treap*& t, std::string s, long long x) {
  while (std::cin >> s >> x) {
    if (s == "insert") {
      if (!Exists(t, x)) {
        Treap* newnode = new Treap(x, rand() % 1000000000, 1);
        Insert(t, newnode);
      }
    }
    if (s == "delete" && Exists(t, x)) {
      Delete(t, x);
    }
    if (s == "exists") {
      if (Exists(t, x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    }
    if (s == "next") {
      long long ans;
      ans = Next(t, x);
      if (ans == -1) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    }
    if (s == "prev") {
      long long ans;
      ans = Prev(t, x);
      if (ans == -1) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    }
    if (s == "kth") {
      long long ans;
      ans = Kth(t, x + 1);
      if (ans == -1) {
        std::cout << "none\n";
      } else {
        std::cout << ans << "\n";
      }
    }
  }
  DeleteTree(t);
}

int main() {
  Treap* t = nullptr;
  std::string s;
  long long x = 0;
  Processing(t, s, x);
}
