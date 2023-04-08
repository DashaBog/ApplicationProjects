#include <iostream>

template <typename T>
struct Node {
  std::pair<T, T> key;
  Node* left;
  Node* right;
  int height;
};

template <typename T>
Node<T>* NewNode(Node<T>* node, T key, T value) {
  node = new Node<T>();
  node->key.first = key;
  node->key.first = key;
  node->key.second = value;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

template <typename T>
int Height(Node<T>* n) {
  if (n == NULL) {
    return 0;
  }
  return n->height;
}

template <typename T>
Node<T>* RightRotate(Node<T>* y) {
  Node<T>* x = y->left;
  Node<T>* switchnode = x->right;
  x->right = y;
  y->left = switchnode;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  return x;
}

template <typename T>
Node<T>* LeftRotate(Node<T>* x) {
  Node<T>* y = x->right;
  Node<T>* switchnode = y->left;
  y->left = x;
  x->right = switchnode;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  return y;
}

template <typename T>
int GetBalance(Node<T>* n) {
  if (n == NULL) {
    return 0;
  }
  return Height(n->left) - Height(n->right);
}

template <typename T>
Node<T>* InsertNode(Node<T>* node, T& key, T& value) {
  if (node == nullptr) {
    return (NewNode(node, key, value));
  }
  if (key < node->key.first) {
    node->left = InsertNode(node->left, key, value);
  } else if (key > node->key.first) {
    node->right = InsertNode(node->right, key, value);
  } else {
    return node;
  }
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  int balance = GetBalance(node);
  if (balance > 1 && key < node->left->key.first) {
    return RightRotate(node);
  }
  if (balance < -1 && key > node->right->key.first) {
    return LeftRotate(node);
  }
  if (balance > 1 && key > node->left->key.first) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  if (balance < -1 && key < node->right->key.first) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

template <typename T>
void Exists(Node<T>* node, T& key) {
  if (node == NULL) {
    return;
  }
  Exists(node->left, key);
  if (node->key.first == key) {
    std::cout << node->key.second << "\n";
    return;
  }
  if (node->key.second == key) {
    std::cout << node->key.first << "\n";
    return;
  }
  Exists(node->right, key);
}

template <typename T>
void DeleteTree(Node<T>* root) {
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

int main() {
  int numtree;
  std::cin >> numtree;
  Node<std::string>* tree = nullptr;
  for (int i = 0; i < numtree; i++) {
    std::string curr, currval;
    std::cin >> currval >> curr;
    tree = InsertNode(tree, currval, curr);
  }
  int numque;
  std::cin >> numque;
  for (int i = 0; i < numque; i++) {
    std::string curr;
    std::cin >> curr;
    Exists(tree, curr);
  }
  DeleteTree(tree);
  return 0;
}