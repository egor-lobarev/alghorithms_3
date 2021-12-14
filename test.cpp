#include <iostream>

using namespace std;

int answer(int n) {
  long long arr[20][3];
  arr[0][0] = arr[0][1] = arr[0][2] = 1;
  for (int i = 1; i < n; i++) {
    arr[i][1] = arr[i][2] = arr[i - 1][0] + arr[i - 1][1] + arr[i - 1][2];
    arr[i][0] = arr[i - 1][1] + arr[i - 1][2];
  }
  for (int i = 0; i < n; i++) {
    cout << arr[i][0] + arr[i][1] + arr[i][2] << endl;
  }
  return arr[n - 1][0] + arr[n - 1][1] + arr[n - 1][2];
}

int main() {
  int N;
  cin >> N;
  cout << answer(N) << endl;
  return 0;
}