#include <iostream>
#include <vector>

void BuildBackpack(std::vector<std::vector<long long>>& optimal,
                   std::vector<std::pair<long long, long long>>& staff,
                   long long size, long long maxweight) {
  for (long long k = 1; k <= size; ++k) {
    for (long long s = 1; s <= maxweight; ++s) {
      if (s >= staff[k].first) {
        optimal[k][s] =
            std::max(optimal[k - 1][s],
                     optimal[k - 1][s - staff[k].first] + staff[k].second);
      } else {
        optimal[k][s] = optimal[k - 1][s];
      }
    }
  }
}

void RecreateArray(std::vector<long long>& answer,
                   std::vector<std::vector<long long>>& optimal,
                   std::vector<std::pair<long long, long long>>& staff,
                   long long k, long long s) {
  if (optimal[k][s] == 0) {
    return;
  }
  if (optimal[k - 1][s] == optimal[k][s]) {
    RecreateArray(answer, optimal, staff, k - 1, s);
  } else {
    RecreateArray(answer, optimal, staff, k - 1, s - staff[k].first);
    answer.push_back(k);
  }
}

int main() {
  long long size;
  long long maxweight;
  std::cin >> size >> maxweight;
  std::vector<std::pair<long long, long long>>
      staff;  // first - weight, second - cost
  staff.push_back({0, 0});
  for (long long i = 0; i < size; ++i) {
    long long input;
    std::cin >> input;
    staff.push_back({input, 0});
  }
  for (long long i = 1; i <= size; ++i) {
    long long input;
    std::cin >> input;
    staff[i].second = input;
  }
  std::vector<std::vector<long long>> optimal(
      size + 1, std::vector<long long>(maxweight + 1, 0));
  BuildBackpack(optimal, staff, size, maxweight);
  std::vector<long long> answer;
  RecreateArray(answer, optimal, staff, size, maxweight);
  for (long unsigned int i = 0; i < answer.size(); ++i) {
    std::cout << answer[i] << "\n";
  }
  return 0;
}