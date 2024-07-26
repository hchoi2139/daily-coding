#include <cstdlib>
#include <iostream>
#include <vector>

struct Coord {
  double x, y;
  Coord(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
};

std::vector<Coord> vs;
int n;

void Input() {
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    double x, y;
    std::cin >> x >> y;
    vs.emplace_back(x, y);
  }
}

[[nodiscard]] double CCW(const Coord& a, const Coord& b, const Coord& c) {
  double res = a.x * b.y + b.x * c.y + c.x * a.y;
  res -= a.y * b.x + b.y * c.x + c.y * a.x;
  return res / 2;
}

double ComputeArea() {
  const Coord pivot = vs[0];
  double res = 0;
  for (int i = 1; i < n - 1; i++) {
    res += CCW(pivot, vs[i], vs[i + 1]);
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed;
  std::cout.precision(1);

  Input();
  const double area = std::abs(ComputeArea());

  std::cout << area;

  return 0;
}
