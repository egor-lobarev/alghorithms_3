#include <iostream>

using namespace std;

struct Object {
  int* arr = nullptr;
  int size = 0;
};

Object RestoreSequence(int** dp, int aSize, int bSize, const int* a, const int* b) {
  int* seq = new int[min(bSize, aSize)];
  int sizeSeq = 0;
  int x = aSize, y = bSize;
  while (x >= 1 && y >= 1) {
    if (a[x - 1] == b[y - 1]) {
      seq[sizeSeq] = a[x - 1];
      x--;
      y--;
      sizeSeq++;
      continue;
    }
    if (x == 1 && y == 1) {
      if (a[0] == b[0]) {
        seq[sizeSeq] = a[0];
        sizeSeq++;
      }
      break;
    }
    int largest = dp[x][y];
    int tmp_x = x;
    int tmp_y = y;
    if (x - 1 >= 1 && dp[x - 1][y] >= largest) {
      largest = dp[x - 1][y];
      tmp_x = x - 1;
      tmp_y = y;
    }
    if (y - 1 >= 1 && dp[x][y - 1] >= largest) {
      tmp_x = x;
      tmp_y = y - 1;
    }
    x = tmp_x;
    y = tmp_y;
  }
  return {seq, sizeSeq};
}

void answer(const int* a, int aSize, const int* b, int bSize) {
  int** dp = new int*[aSize + 1];
  for (int i = 0; i < aSize + 1; i++) {
    dp[i] = new int[bSize + 1];
  }
  for (int i = 0; i < aSize + 1; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i < bSize + 1; i++) {
    dp[0][i] = 0;
  }
  for (int y = 1; y < bSize + 1; y++) {
    for (int x = 1; x < aSize + 1; x++) {
      if (a[x - 1] == b[y - 1]) {
        dp[x][y] = dp[x - 1][y - 1] + 1;
      } else {
        dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]);
      }
    }
  }
  Object obj = RestoreSequence(dp, aSize, bSize, a, b);
  int* seq = obj.arr;
  int sizeSeq = obj.size;
  for (int i = sizeSeq - 1; i >= 0; i--) {
    cout << seq[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < aSize + 1; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] seq;
}

int main() {
  int a_size, b_size;
  cin >> a_size;
  int* a = new int[a_size];
  for (int i = 0; i < a_size; i++) {
    cin >> a[i];
  }
  cin >> b_size;
  int* b = new int[b_size];
  for (int i = 0; i < b_size; i++) {
    cin >> b[i];
  }
  answer(a, a_size, b, b_size);
  delete[] a;
  delete[] b;
  return 0;
}