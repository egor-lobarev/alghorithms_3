#include <iostream>

using namespace std;

void swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void SelectSort(int* a, int size) {
  for (int i = 0; i < size; i++) {
    int min = i;
    for (int j = i + 1; j < size; j++) {
      if (a[j] < a[min]) {
        min = j;
      }
    }
    swap(a[i], a[min]);
  }
}

int Answer(int* arr, int size) {
  SelectSort(arr, size);
  int b[100];
  b[size - 1] = b[size - 2] = abs(arr[size - 1] - arr[size - 2]);
  for (int i = size - 3; i >= 0; i--) {
    b[i] = min(b[i + 1], b[i + 2]) + abs(arr[i] - arr[i + 1]);
  }
  return b[0];
}

int main() {
  int N, *arr = new int[100];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  cout << Answer(arr, N);
  delete[] arr;
}