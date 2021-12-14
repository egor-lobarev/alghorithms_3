#include <iostream>

using namespace std;

struct Coordinates {
  int x;
  int y;
};

Coordinates FindMax(const int* table, int x_now, int y_now, int h, int w, int x_max, int y_max, int prev_most_distant_x, int prev_most_distant_y) {
  int max = table[x_now * y_max + y_now];
  Coordinates max_coords = {x_now, y_now};
  for (int i = x_now; i < min(x_now + h, x_max); i++) {
    for (int j = prev_most_distant_y + 1; j < min(y_now + w, y_max); j++) {
      if (table[i * y_max + j] > max) {
        max = table[i * y_max + j];
        max_coords = {i, j};
      }
    }
  }
  for (int i = prev_most_distant_x + 1; i < min(x_now + h, x_max); ++i) {
    for (int j = y_now; j <= min(prev_most_distant_y, y_max - 1); ++j) {
      if (table[i * y_max + j] > max) {
        max = table[i * y_max + j];
        max_coords = {i, j};
      }
    }
  }
  return max_coords;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int x_max, y_max;
  cin >> x_max >> y_max;
  int* table = new int[x_max * y_max];
  int h, w;
  cin >> h >> w;
  for (int i = 0; i < x_max; i++) {
    for (int j = 0; j < y_max; j++) {
      cin >> table[i * y_max + j];
    }
  }

  int x_now = 0, y_now = 0;
  int max_x;
  int max_y;
  int prev_most_distant_x = -1, prev_most_distant_y = -1;

  while (true) {
    Coordinates max_coords = FindMax(table, x_now, y_now, h, w, x_max, y_max, prev_most_distant_x, prev_most_distant_y);
    max_x = max_coords.x;
    max_y = max_coords.y;
    if ((max_x == prev_most_distant_x && max_y == prev_most_distant_y) || max_x < prev_most_distant_x || max_y < prev_most_distant_y) {
      break;
    }
    prev_most_distant_x = min(x_now + h - 1, x_max - 1);
    prev_most_distant_y = min(y_now + w - 1, y_max - 1);
    x_now = max_x;
    y_now = max_y;
  }
  cout << max_x << " " << max_y;
  delete[] table;
  return 0;
}