#include <iostream>
#include <vector>

void FindAlternativeSequence(std::vector<int64_t>& array) {
  std::vector<std::pair<int64_t, int16_t>> dp_more(array.size(), {1, -1});
  std::vector<std::pair<int64_t, int16_t>> dp_less(array.size(), {1, -1});
  for (size_t i = 1; i < array.size(); ++i) {
    std::pair<int64_t, int16_t> tmp_max = {1, -1};
    std::pair<int64_t, int16_t> tmp_min = {1, -1};
    for (size_t j = 0; j < i; ++j) {
      if (array[j] > array[i]) {
        tmp_max.first = std::max(tmp_max.first, dp_more[j].first + 1);
        if (tmp_max.first == dp_more[j].first + 1) {
          tmp_max.second = j;
        }
      } else if (array[j] < array[i]) {
        tmp_min.first = std::max(tmp_min.first, dp_less[j].first + 1);
        if (tmp_min.first == dp_less[j].first + 1) {
          tmp_min.second = j;
        }
      }
    }
    dp_more[i] = tmp_min;
    dp_less[i] = tmp_max;
  }

  std::pair<int64_t, int16_t> answer = {1, -1};
  int64_t index = 0;
  bool less = false;
  for (size_t i = 0; i < array.size(); ++i) {
    if (answer.first < dp_more[i].first) {
      answer = dp_more[i];
      less = true;
      index = i;
    }
    if (answer.first < dp_less[i].first) {
      answer = dp_less[i];
      less = false;
      index = i;
    }
  }
  std::cout << answer.first << '\n';
  std::vector<int64_t> result(1, array[index]);
  while (answer.second != -1) {
    result.push_back(array[answer.second]);
    if (less) {
      answer = dp_less[answer.second];
    } else {
      answer = dp_more[answer.second];
    }
    less = !less;
  }

  for (size_t i = result.size(); i > 0; --i) {
    std::cout << result[i - 1] << ' ';
  }
}

std::vector<int64_t> Input() {
  size_t size = 0;
  std::cin >> size;
  std::vector<int64_t> array(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  return array;
}

int main() {
  std::vector<int64_t> array = Input();
  FindAlternativeSequence(array);
  return 0;
}