#include <iostream>
#include <vector>

struct Tree {
  const long long kNeitral = 0;
  static const long long kBase = 2;
  long long two_in_power_ = 1;
  long long size_ = 0;
  std::vector<long long> body_;
  std::vector<std::pair<long long, long long>> l_r_;
  std::vector<std::pair<long long, long long>> kids_;
};

void CreateTree(Tree& tree, long long size) {
  tree.size_ = size;
  while (tree.two_in_power_ < size) {
    tree.two_in_power_ *= Tree::kBase;
  }
  tree.body_.reserve(Tree::kBase * tree.two_in_power_);
}

void ToBuildTree(Tree& tree) {
  while ((long long) tree.body_.size() < tree.two_in_power_) {
    tree.body_.push_back(tree.kNeitral);
  }
  long long id = 0;
  for (long long i = 0; i < (long long) tree.body_.size(); ++i) {
    tree.l_r_.push_back(std::make_pair(i, i + 1));
    tree.kids_.push_back(std::make_pair(-1, -1));
  }
  while (id + 1 != (long long) tree.body_.size()) {
    tree.body_.push_back(tree.body_[id] + tree.body_[id + 1]);
    tree.l_r_.push_back(std::make_pair(tree.l_r_[id].first, tree.l_r_[id + 1].second));
    tree.kids_.push_back(std::make_pair(id, id + 1));
    id += 2;
  }
}

void ChangeTree(Tree& tree, long long id, long long new_val) {
  long long delta = new_val - tree.body_[id];
  tree.body_[id] = new_val;
  size_t dist = tree.body_.size() / 2;
  size_t way = dist + 1;
  while (dist <= 1) {
    tree.body_[way + id / 2] += delta;
    ++dist /= 2;
    id /= 2;
    way += dist;
  }
}

long long GetSum(Tree& tree, long long id, long long ltx, long long rtx) {
  if (tree.l_r_[id].first >= rtx || ltx >= tree.l_r_[id].second) {
    return 0;
  }
  if (ltx <= tree.l_r_[id].first && rtx >= tree.l_r_[id].second) {
    return tree.body_[id];
  }
  long long s1;
  long long s2;
  if (tree.kids_[id].first == -1) {
    s1 = 0;
  } else {
    s1 = GetSum(tree, tree.kids_[id].first, ltx, rtx);
  }
  if (tree.kids_[id].second == -1) {
    s2 = 0;
  } else {
    s2 = GetSum(tree, tree.kids_[id].second, ltx, rtx);
  }
  return s1 + s2;
}

int main() {
  long long size;
  std::cin >> size;
  Tree t1;
  Tree t2;
  CreateTree(t1, size);
  CreateTree(t2, size);
  for (long long i = 0; i < size; ++i) {
    long long input;
    std::cin >> input;
    if ((i & 1) == 1) {
      t1.body_.push_back(input);
      t2.body_.push_back(-input);
    } else {
      t1.body_.push_back(-input);
      t2.body_.push_back(input);
    }
  }
  ToBuildTree(t1);
  ToBuildTree(t2);
  long long num;
  std::cin >> num;
  long long request;
  long long lt;
  long long rt;
  for (long long i = 0; i < num; ++i) {
    std::cin >> request;
    std::cin >> lt >> rt;
    switch (request) {
      case 0:
        if ((lt & 1) == 1) {
          ChangeTree(t2, lt - 1, rt);
          ChangeTree(t1, lt - 1, -rt);
        } else {
          ChangeTree(t2, lt - 1, -rt);
          ChangeTree(t1, lt - 1, rt);
        }
        break;
      case 1:
        if ((lt & 1) == 1) {
          std::cout << GetSum(t2, t2.body_.size() - 1, lt - 1, rt) << '\n';
        } else {
          std::cout << GetSum(t1, t1.body_.size() - 1, lt - 1, rt) << '\n';
        }
        break;
    }
  }
}