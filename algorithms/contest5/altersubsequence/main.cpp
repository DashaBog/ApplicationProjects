#include <algorithm>
#include <iostream>
#include <vector>

long long Max(long long a, long long b) { return (a > b) ? a : b; }

struct Condition {
  long long answer;
  long long position;
  bool numberofs;  // 0 - first subsequence, 1 - second subsequence
};

Condition LIS(std::vector<std::pair<long long, long long>>& lis_lengthmore,
              std::vector<std::pair<long long, long long>>& lis_lengthless,
              std::vector<long long>& sequence, long long sizesequence) {
  lis_lengthmore[0] = {1, -1};
  lis_lengthless[0] = {1, -1};
  for (long long i = 1; i < sizesequence; ++i) {
    std::pair<long long, long long> tmp_max = {1, -1};
    std::pair<long long, long long> tmp_min = {1, -1};
    for (long long j = 0; j < i; ++j) {
      if (sequence[j] > sequence[i]) {
        tmp_max.first = Max(tmp_max.first, lis_lengthmore[j].first + 1);
        if (tmp_max.first == lis_lengthmore[j].first + 1) {
          tmp_max.second = j;
        }
      } else if (sequence[j] < sequence[i]) {
        tmp_min.first = Max(tmp_min.first, lis_lengthless[j].first + 1);
        if (tmp_min.first == lis_lengthless[j].first + 1) {
          tmp_min.second = j;
        }
      }
    }
    lis_lengthmore[i] = tmp_min;
    lis_lengthless[i] = tmp_max;
  }
  Condition length;
  length.answer = lis_lengthmore[0].first;
  length.position = 0;
  length.numberofs = false;
  for (long long i = 0; i < sizesequence; ++i) {
    if (lis_lengthmore[i].first > length.answer) {
      length.answer = lis_lengthmore[i].first;
      length.position = i;
      length.numberofs = false;
    }
  }
  for (long long i = 0; i < sizesequence; ++i) {
    if (lis_lengthless[i].first > length.answer) {
      length.answer = lis_lengthless[i].first;
      length.position = i;
      length.numberofs = true;
    }
  }
  return length;
}

void GetSequence(Condition length,
                 std::vector<std::pair<long long, long long>>& lis_lengthmore,
                 std::vector<std::pair<long long, long long>>& lis_lengthless,
                 std::vector<long long>& sequence) {
  std::vector<long long> path;
  for (long long i = 0; i < length.answer; ++i) {
    if (length.position != -1) {
      if (length.numberofs) {
        path.push_back(sequence[length.position]);
        length.position = lis_lengthless[length.position].second;
        length.numberofs = !length.numberofs;
      } else {
        path.push_back(sequence[length.position]);
        length.position = lis_lengthmore[length.position].second;
        length.numberofs = !length.numberofs;
      }
    }
  }

  std::reverse(path.begin(), path.end());

  for (unsigned long long i = 0; i < path.size(); ++i) {
    std::cout << path[i] << ' ';
  }
}

int main() {
  long long sizesequence;
  std::cin >> sizesequence;
  std::vector<long long> sequence;
  for (long long i = 0; i < sizesequence; ++i) {
    long long input;
    std::cin >> input;
    sequence.push_back(input);
  }
  std::vector<std::pair<long long, long long>>
      lis_lengthmore;  // > first - length, second - postion
  std::vector<std::pair<long long, long long>> lis_lengthless;  // <
  lis_lengthmore.resize(sizesequence);
  lis_lengthless.resize(sizesequence);
  Condition length =
      LIS(lis_lengthmore, lis_lengthless, sequence, sizesequence);
  std::cout << length.answer << "\n";
  GetSequence(length, lis_lengthmore, lis_lengthless, sequence);
  return 0;
}