#include <iostream>
#include <cstring>

using namespace std;

void answer(const char* a, int aSize, const char* b, int bSize) {
  int** dp = new int*[aSize + 1];
  for (int i = 0; i < aSize + 1; i++) {
    dp[i] = new int[bSize + 1];
  }

  dp[0][0] = 0;
  for (int i = 1; i < aSize + 1; i++) {
    dp[i][0] = i;
  }
  for (int i = 1; i < bSize + 1; i++) {
    dp[0][i] = i;
  }
  for (int y = 1; y < bSize + 1; y++) {
    for (int x = 1; x < aSize + 1; x++) {
      int smallest = dp[x][y - 1] + 1;
      if (dp[x - 1][y] + 1 <= smallest) {
        smallest = dp[x - 1][y] + 1;
      }
      int areCoincide = (a[x - 1] != b[y - 1] ? 1 : 0);
      if (dp[x - 1][y - 1] + areCoincide <= smallest) {
        smallest = dp[x - 1][y - 1] + areCoincide;
      }
      dp[x][y] = smallest;
    }
  }
  cout << dp[aSize][bSize];
  for (int i = 0; i < aSize + 1; i++) {
    delete[] dp[i];
  }
  delete[] dp;
}

int main() {
  char* a = new char[5000];
  char* b = new char[5000];
  cin >> a;
  cin >> b;
  int aSize = strlen(a);
  int bSize = strlen(b);
  answer(a, aSize, b, bSize);
  delete[] a;
  delete[] b;
  return 0;
}