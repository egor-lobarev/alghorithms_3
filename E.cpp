#include <iostream>

using namespace std;

void swap(long& a, long& b) {
  long tmp = a;
  a = b;
  b = tmp;
}

long Pow(long number, long power) {
  long pow;
  if (power > 0) {
    pow = Pow(number, power / 2) * Pow(number, power / 2);
    if (power % 2 == 1) {
      pow *= number;
    }
  } else {
    pow = 1;
  }
  return pow;
}

long NumOfPatterns(long** numberOfPatterns, long numberOfCols, long& numberOfPossibleCols) {
  long totalNumberOfPatterns = 0;
  for (long i = 0; i < numberOfPossibleCols; ++i) {
    totalNumberOfPatterns += numberOfPatterns[numberOfCols - 1][i];
  }
  return totalNumberOfPatterns;
}

bool CanColsBeNear(long colSize, long firstColNumber, long secondColNumber) {
  long square_sum;
  for (long i = 0; i < colSize - 1; i++) {
    square_sum = ((firstColNumber >> i) & 1) + ((secondColNumber >> i) & 1);
    square_sum += ((firstColNumber >> (i + 1)) & 1) + ((secondColNumber >> (i + 1)) & 1);
    if (square_sum == 0 || square_sum == 4) {
      return false;
    }
  }
  return true;
}

void CalculateNumOfPatterns(long numOfCols, bool** canColsBeNear, long** numberOfPatterns, long& number_of_possible_columns) {
  for (long i = 0; i < number_of_possible_columns; i++) {
    numberOfPatterns[0][i] = 1;
  }
  for (long i = 1; i < numOfCols; i++) {
    for (long j = 0; j < number_of_possible_columns; j++) {
      for (long k = 0; k < number_of_possible_columns; k++) {
        if (canColsBeNear[j][k]) {
          numberOfPatterns[i][j] += numberOfPatterns[i - 1][k];
        }
      }
    }
  }
}

void CalculateColsCanBeNear(const long& colsSize, const long& numOfPossibleCols, bool** canColsBeNear) {
  for (long i = 0; i < numOfPossibleCols; i++) {
    for (long j = 0; j < numOfPossibleCols; j++) {
      if (i <= j) {
        if (CanColsBeNear(colsSize, i, j)) {
          canColsBeNear[j][i] = canColsBeNear[i][j] = true;
        }
      }
    }
  }
}

int main() {
  long n, m;
  cin >> n >> m;
  if (n > m) {
    swap(n, m);
  }
  long numOfPossibleCols = Pow(2, n);
  long** numberOfPatterns = new long*[m];
  for (long i = 0; i < m; i++) {
    numberOfPatterns[i] = new long[numOfPossibleCols]();
  }
  bool** canColsBeNear = new bool*[numOfPossibleCols];
  for (long i = 0; i < numOfPossibleCols; i++) {
    canColsBeNear[i] = new bool[numOfPossibleCols]();
  }

  CalculateColsCanBeNear(n, numOfPossibleCols, canColsBeNear);
  CalculateNumOfPatterns(m, canColsBeNear, numberOfPatterns, numOfPossibleCols);
  cout << NumOfPatterns(numberOfPatterns, m, numOfPossibleCols);

  for (long i = 0; i < numOfPossibleCols; i++) {
    delete[] canColsBeNear[i];
  }
  delete[] canColsBeNear;
  for (long i = 0; i < m; ++i) {
    delete[] numberOfPatterns[i];
  }
  delete[] numberOfPatterns;
  return 0;
}