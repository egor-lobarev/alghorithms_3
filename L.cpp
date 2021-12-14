#include <iostream>

using namespace std;

struct Array {
  int* arr;
  int size;
};

void Print(Array tmp) {
  int size = tmp.size;
  for (int i = 0; i < size; i++) {
    cout << tmp.arr[i] << endl;
  }
}

Array RestoreItems(int** dp, int n, int capacity, const int* weight) {
  int j = capacity;
  int* seq = new int[n];
  int size_seq = 0;
  for (int i = n; i > 0 && j >= 0; i--) {
    if (dp[i][j] == dp[i - 1][j]) {
      continue;
    }
    seq[size_seq] = i;
    size_seq++;
    j -= weight[i - 1];
  }
  for (int i = 0; i < size_seq / 2; i++) {
    swap(seq[i], seq[size_seq - i - 1]);
  }
  return {seq, size_seq};
}

void solve(int n, int capacity, const int* weight, const int* cost) {
  int** dp = new int*[n + 1];
  for (int i = 0; i < n + 1; i++) {
    dp[i] = new int[capacity + 1];
  }
  for (int i = 0; i < capacity + 1; i++) {
    dp[0][i] = 0;
  }
  for (int i = 0; i < n + 1; i++) {
    dp[i][0] = 0;
  }

  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < capacity + 1; j++) {
      int largest = dp[i - 1][j];
      if (j - weight[i - 1] >= 0 && dp[i - 1][j - weight[i - 1]] + cost[i - 1] > largest) {
        largest = dp[i - 1][j - weight[i - 1]] + cost[i - 1];
      }
      dp[i][j] = largest;
    }
  }

  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < capacity + 1; j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }

  Array tmp = RestoreItems(dp, n, capacity, weight);
  Print(tmp);

  for (int i = 0; i < n + 1; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] tmp.arr;
}

int main() {
  int N, capacity;
  cin >> N >> capacity;
  int* weight = new int[N];
  int* cost = new int[N];
  for (int i = 0; i < N; i++) {
    cin >> weight[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> cost[i];
  }
  solve(N, capacity, weight, cost);
  delete[] weight;
  delete[] cost;
  return 0;
}