#include <iostream>

using namespace std;

void answer(const int* arr, int size) {
  int* b = new int[size];
  for (int i = 0; i < size; i++) {
    b[i] = 1;
  }
  for (int i = 0; i < size; i++) {
    int max_ind = -1;
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && (max_ind == -1 || b[j] > b[max_ind])) {
        max_ind = j;
      }
      if (max_ind != -1) {
        b[i] = b[max_ind] + 1;
      }
    }
  }
  int max = b[size - 1];
  for (int i = size - 2; i >= 0; i--) {
    if (b[i] > max) {
      max = b[i];
    }
  }
  cout << max << endl;
  delete[] b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  int* arr = new int[N];
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  answer(arr, N);
  delete[] arr;
  return 0;
}