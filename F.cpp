#include <iostream>

using namespace std;

void solve(int numberOfRoads, int numberOfLanes) {
  int** dp = new int*[numberOfLanes];
  for (int i = 0; i < numberOfLanes; i++) {
    dp[i] = new int[numberOfRoads];
  }

  for (int i = 0; i < numberOfLanes; i++) {
    dp[i][0] = 1;
  }
  for (int i = 0; i < numberOfRoads; i++) {

  }

  for (int j = 0; j < numberOfRoads; j++) {
    for (int i = 0; i < numberOfLanes; i++) {
      if (i == 0 && j == 0) {
        continue;
      }
      int sum = 0;
      if (i > 0 && j > 0) {
        sum += dp[i - 1][j - 1];
      }
      if (j > 0) {
        sum += dp[i][j - 1];
      }
      if (i > 0) {
        sum += dp[i - 1][j];
      }
      dp[i][j] = sum % 1000000;
    }
  }

  for (int i = 0; i < numberOfLanes; i++) {
    for (int j = 0; j < numberOfRoads; j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }

  cout << dp[numberOfLanes - 1][numberOfRoads - 1];

  for (int i = 0; i < numberOfLanes; i++) {
    delete[] dp[i];
  }
  delete[] dp;
}

int main() {
  int numberOfRoads, numberOfLanes;
  cin >> numberOfRoads >> numberOfLanes;
  solve(numberOfRoads, numberOfLanes);
  return 0;
}