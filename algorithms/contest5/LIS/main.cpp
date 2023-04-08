#include <algorithm>
#include <iostream>
#include <vector>

long long UpperBound(std::vector<long long>& sequence, long long left,
                     long long right, long long key) {
  while (right - left > 1) {
    long long mid = left + (right - left) / 2;
    if (sequence[mid] >= key) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

long long LISLength(std::vector<long long>& sequence) {
  if (sequence.empty()) {
    return 0;
  }
  std::vector<long long> tail(sequence.size() + 2, 0);
  long long length = 1;
  tail[0] = sequence[0];
  for (long unsigned int i = 1; i < sequence.size(); i++) {
    if (sequence[i] < tail[0]) {
      tail[0] = sequence[i];
    } else if (sequence[i] > tail[length - 1]) {
      tail[length] = sequence[i];
      length++;
    } else {
      // long long foundpos = std::upper_bound(tail.begin(), tail[length - 1],
      // sequence[i]) - tail.begin() - 1;
      long long foundpos = UpperBound(tail, -1, length - 1, sequence[i]);
      tail[foundpos] = sequence[i];
    }
  }
  return length;
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
  std::cout << LISLength(sequence) << '\n';
  return 0;
}