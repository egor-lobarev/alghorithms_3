#include <iostream>

using namespace std;

bool IsCellWithNumber(int x, int y) {
  return ((x != 0 || y != 3) && (x != 2 || y != 3));
}

bool IsHorseMove(int x1, int y1, int x2, int y2) {
  return ((abs(x1 - x2) == 1 && abs(y1 - y2) == 2) || (abs(x1 - x2) == 2 && abs(y1 - y2) == 1));
}

long long answer(int n) {
  long long arr[20][3][4] = {};
  arr[0][0][0] = arr[0][0][1] = arr[0][0][2] = arr[0][1][1] = arr[0][1][2] = arr[0][2][0] = arr[0][2][1] = arr[0][2][2] = 1;
  arr[0][1][0] = arr[0][1][3] = 0;
  for (int i = 1; i < n; i++) {
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 4; y++) {
        for (int x_prev = 0; x_prev < 3; x_prev++) {
          for (int y_prev = 0; y_prev < 4; y_prev++) {
            if (IsHorseMove(x, y, x_prev, y_prev) && IsCellWithNumber(x, y) && IsCellWithNumber(x_prev, y_prev)) {
              arr[i][x][y] += arr[i - 1][x_prev][y_prev];
            }
          }
        }
      }
    }
  }
  long long cnt = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 4; y++) {
      if ((x != 0 || y != 3) && (x != 2 || y != 3)) {
        cnt += arr[n - 1][x][y];
      }
    }
  }
  return cnt;
}

int main() {
  int N;
  cin >> N;
  cout << answer(N) << endl;
  return 0;
}