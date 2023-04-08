#include <iostream>

int** MakeSpiral(int n) {
  int** matrix = new int*[n];
  for (int i = 0; i < n; i++) {
    matrix[i] = new int[n];
  }
  int i = 1;
  int j;
  int loop;
  int p = n / 2;
  for (loop = 1; loop <= p; loop++) {
    for (j = loop - 1; j < n - loop + 1; j++) {
      matrix[loop - 1][j] = i++;
    }
    for (j = loop; j < n - loop + 1; j++) {
      matrix[j][n - loop] = i++;
    }
    for (j = n - loop - 1; j >= loop - 1; --j) {
      matrix[n - loop][j] = i++;
    }
    for (j = n - loop - 1; j >= loop; j--) {
      matrix[j][loop - 1] = i++;
    }
  }
  if (n % 2 == 1) {
    matrix[p][p] = n * n;
  }
  return matrix;
}

int main() {
  int n = 10;
  int** matrix = MakeSpiral(n);
  for(int i = 0; i < n; i++)
    for(int j=0; j<n; j++)
    {
      printf(" %4d ",matrix[i][j]);
      if(j==n-1) printf("\n");
    }
}