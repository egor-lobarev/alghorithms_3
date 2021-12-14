#include <iostream>

using namespace std;

void answer(const int* arr, int size) {
  long long b[100];
  for (int i = 0; i < size; i++) {
    b[i] = 1;
  }
  for (int i = 1; i < size; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j]) {
        b[i] += b[j] % 1000000;
      }
    }
  }
  long long s = 0;
  for (int i = 0; i < size; i++) {
    s += b[i];
    s %= 1000000;
  }
  cout << s << endl;
}

int main() {
  int N;
  cin >> N;
  int arr[100];
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  answer(arr, N);
  return 0;
}