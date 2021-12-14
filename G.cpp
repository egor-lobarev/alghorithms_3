#include <iostream>

using namespace std;

int answer(int n) {
  int* arr = new int[n + 1];
  arr[1] = 0;
  for (int i = 2; i <= n; i++) {
    int smallest = 1000000000;
    if (i % 2 == 0 && i / 2 > 0 && arr[i / 2] < smallest) {
      smallest = arr[i / 2];
    }
    if (i % 3 == 0 && i / 3 > 0 && arr[i / 3] < smallest) {
      smallest = arr[i / 3];
    }
    if (i - 1 > 0 && arr[i - 1] < smallest) {
      smallest = arr[i - 1];
    }
    arr[i] = smallest + 1;
  }
  int ans = arr[n];
  delete[] arr;
  return ans;
}

int main() {
  int N;
  cin >> N;
  cout << answer(N) << endl;
  return 0;
}