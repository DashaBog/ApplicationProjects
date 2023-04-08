#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  int height;
};

Node* NewNode(int key) {
  Node* node = new Node();
  node->key = key;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 1;
  return node;
}

int Height(Node* n) {
  if (n == nullptr) {
    return 0;
  }
  return n->height;
}

Node* RightRotate(Node* y) {
  Node* x = y->left;
  Node* swaptree = x->right;
  x->right = y;
  y->left = swaptree;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  return x;
}

Node* LeftRotate(Node* x) {
  Node* y = x->right;
  Node* swaptree = y->left;
  y->left = x;
  x->right = swaptree;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  return y;
}

int GetBalance(Node* n) {
  if (n == nullptr) {
    return 0;
  }
  return Height(n->left) - Height(n->right);
}

Node* InsertNode(Node* node, int key) {
  if (node == nullptr) {
    return (NewNode(key));
  }
  if (key < node->key) {
    node->left = InsertNode(node->left, key);
  } else if (key >= node->key) {
    node->right = InsertNode(node->right, key);
  }
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  int balance = GetBalance(node);
  if (balance > 1 && key < node->left->key) {
    return RightRotate(node);
  }
  if (balance < -1 && key >= node->right->key) {
    return LeftRotate(node);
  }
  if (balance > 1 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

int Next(Node* t, int x) {
  if (t->key == x) {
    return x;
  }
  if (t->key > x) {
    if (t->left != nullptr) {
      int currentcheck = Next(t->left, x);
      if (currentcheck == -1) {
        return t->key;
      }
      return currentcheck;
    }
  }
  if (t->key < x) {
    if (t->right != nullptr) {
      return Next(t->right, x);
    }
    return -1;
  }
  return t->key;
}

Node* Processing(Node* tree, std::string s, int n) {
  char lastpros = '+';
  int number;
  int lastnext = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> s >> number;
    if (s == "+" && lastpros == '+') {
      tree = InsertNode(tree, number);
    } else if (s == "+" && lastpros == '?') {
      tree = InsertNode(tree, (number + lastnext) % 1000000000);
      lastpros = '+';
    } else if (s == "?") {
      lastnext = Next(tree, number);
      std::cout << lastnext << "\n";
      lastpros = '?';
    }
  }
  return tree;
}

void DeleteTree(Node* root) {
  if (root->left != nullptr) {
    DeleteTree(root->left);
    root->left = nullptr;
  }
  if (root->right != nullptr) {
    DeleteTree(root->right);
    root->right = nullptr;
  }
  delete root;
}

int main() {
  int n;
  std::cin >> n;
  Node* tree = nullptr;
  std::string s;
  tree = Processing(tree, s, n);
  DeleteTree(tree);
  return 0;
}