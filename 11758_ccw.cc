#include <iostream>
#include <utility>

using ii = std::pair<int, int>;

struct Coord {
  int x, y;
  Coord(const int x_coord, const int y_coord) : x(x_coord), y(y_coord) {}
};

[[nodiscard]] int CCW(const Coord& c1, const Coord& c2, const Coord& c3) {
  const ii a = { c2.x - c1.x, c2.y - c1.y };
  const ii b = { c3.x - c1.x, c3.y - c1.y };
  return a.first * b.second - a.second * b.first;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x, y;

  std::cin >> x >> y;
  const Coord p1 = { x, y };

  std::cin >> x >> y;
  const Coord p2 = { x, y };

  std::cin >> x >> y;
  const Coord p3 = { x, y };

  int cp = CCW(p1, p2, p3);

  if (cp == 0) {
    std::cout << 0;
  } else {
    std::cout << (cp > 0 ? 1 : -1);
  }

  return 0;
}
