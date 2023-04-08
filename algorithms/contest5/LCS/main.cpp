#include <iostream>
#include <vector>

void BuildLCSTable(std::vector<std::vector<long long>>& dp,
                   std::vector<long long>& x, std::vector<long long>& y,
                   long long sizefirst, long long sizesecond) {
  for (int i = 0; i <= sizefirst; i++) {
    for (int j = 0; j <= sizesecond; j++) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (x[i - 1] == y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
}

void CreateSequence(std::vector<std::vector<long long>>& dp,
                    std::vector<long long>& x, std::vector<long long>& y,
                    long long sizefirst, long long sizesecond) {
  long long index = dp[sizefirst][sizesecond];
  std::vector<long long> sequence(index + 1);
  long long dpsize = index;
  long long i = sizefirst;
  long long j = sizesecond;
  while (i > 0 && j > 0) {
    if (x[i - 1] == y[j - 1]) {
      sequence[index] = x[i - 1];
      --i;
      --j;
      --index;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }
  for (long long k = 1; k <= dpsize; ++k) {
    std::cout << sequence[k] << " ";
  }
}

int main() {
  long long sizefirst;
  std::cin >> sizefirst;
  std::vector<long long> firstsequence;
  for (long long i = 0; i < sizefirst; ++i) {
    long long value;
    std::cin >> value;
    firstsequence.push_back(value);
  }
  long long sizesecond;
  std::cin >> sizesecond;
  std::vector<long long> secondsequence;
  for (long long i = 0; i < sizesecond; ++i) {
    long long value;
    std::cin >> value;
    secondsequence.push_back(value);
  }
  std::vector<std::vector<long long>> dp(
      sizefirst + 1, std::vector<long long>(sizesecond + 1));
  BuildLCSTable(dp, firstsequence, secondsequence, sizefirst, sizesecond);
  CreateSequence(dp, firstsequence, secondsequence, sizefirst, sizesecond);
  return 0;
}