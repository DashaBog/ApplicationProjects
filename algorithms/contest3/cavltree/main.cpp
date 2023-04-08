#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  int height;
  ~Node() {
    free(left);
    free(right);
  }
};

Node* newNode(int key) {
  Node* node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

int height(Node* N) {
  if (N == NULL)
    return 0;
  return N->height;
}

Node* rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  free(T2);
  return x;
}

Node* leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  free(T2);
  return y;
}

int getBalance(Node* N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

Node* InsertNode(Node* node, int key) {
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = InsertNode(node->left, key);
  else if (key > node->key)
    node->right = InsertNode(node->right, key);
  else return node;
  node->height = 1 + std::max(height(node->left), height(node->right));
  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  return node;
}

Node* minValueNode(Node* node) {
  Node* current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

Node* DeleteNode(Node* root, int key) {
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = DeleteNode(root->left, key);
  else if (key > root->key)
    root->right = DeleteNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      Node* temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else { *root = *temp; }
      free(temp);
    } else {
      Node* temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = DeleteNode(root->right, temp->key);
      free(temp);
    }
  }
  if (root == NULL)
    return root;
  root->height = 1 + std::max(height(root->left), height(root->right));
  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void Exists(Node* node, int key, bool* notfound) {
  if (node == NULL) {
    return;
  }
  Exists(node->left, key, notfound);
  if (node->key == key) {
    *notfound = false;
    return;
  }
  Exists(node->right, key, notfound);
}

void Next(Node* t, int x) {
  if (t == nullptr) {
    std::cout << "none" << std::endl;
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
}

void Prev(Node* t, int x) {
  if (t == nullptr) {
    std::cout << "none" << std::endl;
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
}

void Kth(Node* tree, int x) {
  if (height(tree) == x + 1) {
    std::cout << tree->key << std::endl;
    return;
  }
  if (height(tree->left) >= x + 1) {
    if (tree->left == nullptr) {
      std::cout << "none" << std::endl;
      return;
    }
    return Kth(tree->left, x);
  }
  if (height(tree->left) < x + 1) {
    if (tree->right == nullptr) {
      std::cout << "none" << std::endl;
      return;
    }
    return Kth(tree->right, x - height(tree->left) - 1);
  }
  std::cout << "none" << std::endl;
  return;
}

Node* Processing(Node* tree) {
  while (std::cin >> s && s != "\n") {
    std::cin >> x;
    if (s == "insert") {
      tree = InsertNode(tree, x);
    } else if (s == "delete") {
      tree = DeleteNode(tree, x);
    } else if (s == "exists") {
      bool notfound = true;
      Exists(tree, x, &notfound);
      if (notfound) {
        std::cout << "false\n";
      } else {
        std::cout << "true\n";
      }
    } else if (s == "next") {
      Next(tree, x);
    } else if (s == "prev") {
      Prev(tree, x);
    } else if (s == "kth") {
      Kth(tree, x);
    }
  }
  return tree;
}

int main() {
  int x = 0;
  Node* tree = nullptr;
  tree = Processing(tree);
  free(tree);
  return 0;
}