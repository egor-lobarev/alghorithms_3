#include <iostream>

using namespace std;

int LowerBound(const int* arr, int size, int x) {
  int right = size;
  int left = 0;
  int pivot;
  while (right > left) {
    pivot = left + (right - left) / 2;
    if (x <= arr[pivot]) {
      right = pivot;
    } else {
      left = pivot + 1;
    }
  }
  return left;
}

void Solve(int* arr, int n) {
  int* dp = new int[n + 1];
  dp[0] = -100001;
  for (int i = 1; i < n + 1; i++) {
    dp[i] = 100001;
  }
  for (int i = 0; i < n; i++) {
    int ind = LowerBound(dp, n + 1, arr[i]);
    dp[ind] = arr[i];
  }
  int cnt = 0;
  for (int i = 1; i < n + 1; i++) {
    if (dp[i] > -100001 && dp[i] < 100001) {
      cnt++;
    } else if (cnt != 0) {
      break;
    }
  }
  cout << cnt;
  delete[] dp;
}

int main() {
  int N;
  cin >> N;
  int* arr = new int[N];
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  Solve(arr, N);
  delete[] arr;
  return 0;
}