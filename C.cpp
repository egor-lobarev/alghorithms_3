#include <iostream>

using namespace std;

long long answer(int n) {
  long long arr[100][2];
  arr[0][0] = arr[0][1] = 1;
  for (int i = 1; i < n; i++) {
    arr[i][0] = arr[i - 1][0] + arr[i - 1][1];
    arr[i][1] = arr[i - 1][0];
  }
  return arr[n - 1][0] + arr[n - 1][1];
}

int main() {
  int N;
  cin >> N;
  cout << answer(N) << endl;
  return 0;
}