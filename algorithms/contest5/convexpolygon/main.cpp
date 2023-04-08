#include <iostream>
#include <vector>

long long CrossProduct(std::vector<std::pair<long long, long long>>& edjesmatrix) {
  long long matrix11 = edjesmatrix[1].first - edjesmatrix[0].first;
  long long matrix12 = edjesmatrix[2].first - edjesmatrix[0].first;
  long long matrix21 = edjesmatrix[1].second - edjesmatrix[0].second;
  long long matrix22 = edjesmatrix[2].second - edjesmatrix[0].second;
  return (matrix11 * matrix22 - matrix21 * matrix12);
}

bool IsConvex(std::vector<std::pair<long long, long long>>& points) {
  long long  size = points.size();
  long long  prev = 0;
  long long  curr = 0;
  for (long long  i = 0; i < size; i++) {
    std::vector<std::pair<long long, long long>> edjesmatrix;
    edjesmatrix.push_back(points[i]);
    edjesmatrix.push_back(points[(i + 1) % size]);
    edjesmatrix.push_back(points[(i + 2) % size]);
    curr = CrossProduct(edjesmatrix);
    if (curr != 0) {
      if (curr * prev < 0) {
        return false;
      } else {
        prev = curr;
      }
    }
  }
  return true;
}

int main() {
  long long size;
  std::cin >> size;
  std::vector<std::pair<long long, long long>> polygon;
  for (long long i = 0; i < size; ++i) {
    long long x;
    long long y;
    std::cin >> x >> y;
    polygon.push_back(std::make_pair(x, y));
  }
  if (IsConvex(polygon)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}