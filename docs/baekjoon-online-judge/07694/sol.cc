#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Inputs.
struct Point2D {
  int x;
  int y;
};

struct Polygon2D {
  vector<Point2D> exterior;
};

// Solution.
int ComputeGcd(int a, int b) {
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

double ComputeArea(const Polygon2D& polygon) {
  double sum = 0.0;
  for (std::size_t idx = 0; idx < polygon.exterior.size(); ++idx) {
    const auto& from = polygon.exterior[idx];
    const auto& to = polygon.exterior[(idx + 1) % polygon.exterior.size()];
    sum += from.x * to.y - from.y * to.x;
  }
  return 0.5 * abs(sum);
}

int CountLatticePointsOnExterior(const Polygon2D& polygon) {
  int ret = 0;
  for (std::size_t idx = 0; idx < polygon.exterior.size(); ++idx) {
    const auto& from = polygon.exterior[idx];
    const auto& to = polygon.exterior[(idx + 1) % polygon.exterior.size()];
    const auto dx = abs(from.x - to.x);
    const auto dy = abs(from.y - to.y);
    if (dx == 0) {
      ret += dy;
    } else if (dy == 0) {
      ret += dx;
    } else {
      auto gcd = ComputeGcd(dx, dy);
      ret += dx / (dx / gcd);
    }
  }
  return ret;
}

int Solution(const Polygon2D& polygon) {
  double area = ComputeArea(polygon);
  int lattice_points_on_exterior = CountLatticePointsOnExterior(polygon);
  return static_cast<int>(area - lattice_points_on_exterior / 2 + 1);
}

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs.
  while (true) {
    Polygon2D polygon{{3, Point2D{0, 0}}};
    cin >> polygon.exterior[0].x >> polygon.exterior[0].y >>
        polygon.exterior[1].x >> polygon.exterior[1].y >>
        polygon.exterior[2].x >> polygon.exterior[2].y;
    if (polygon.exterior[0].x == 0 && polygon.exterior[0].y == 0 &&
        polygon.exterior[1].x == 0 && polygon.exterior[1].y == 0 &&
        polygon.exterior[2].x == 0 && polygon.exterior[2].y == 0) {
      break;
    } else {
      // Solve.
      cout << Solution(polygon) << '\n';
    }
  }

  return 0;
}