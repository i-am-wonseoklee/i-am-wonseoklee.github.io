#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Inputs.
class Vector2D;
int N;
vector<Vector2D> P;

// Solution.
constexpr double kEpsilon = 1e-9;

class Vector2D {
 public:
  Vector2D() = default;
  Vector2D(double x, double y) : x_(x), y_(y) {}

  double x() const { return x_; }
  double y() const { return y_; }

  Vector2D operator+(const Vector2D& rhs) const {
    return Vector2D(x_ + rhs.x_, y_ + rhs.y_);
  }
  Vector2D operator-(const Vector2D& rhs) const {
    return Vector2D(x_ - rhs.x_, y_ - rhs.y_);
  }
  bool operator<=(const Vector2D& rhs) const {
    if (x_ != rhs.x_) {
      return x_ <= rhs.x_;
    }
    return y_ <= rhs.y_;
  }
  double GetCcw(const Vector2D& v) const { return x_ * v.y_ - y_ * v.x_; }
  double GetAzimuth() const { return atan2(y_, x_); }
  double GetSquaredNorm() const { return x_ * x_ + y_ * y_; }

 private:
  double x_ = 0.0;
  double y_ = 0.0;
};

size_t Solve() {
  int lowest_point_idx = 0;
  for (int i = 1; i < N; ++i) {
    if (P[i] <= P[lowest_point_idx]) {
      lowest_point_idx = i;
    }
  }
  swap(P[0], P[lowest_point_idx]);
  sort(P.begin() + 1, P.end(),
       [p = P[0]](const Vector2D& lhs, const Vector2D& rhs) {
         const auto lhs_angle = (lhs - p).GetAzimuth();
         const auto rhs_angle = (rhs - p).GetAzimuth();
         if (abs(lhs_angle - rhs_angle) > kEpsilon) {
           return lhs_angle < rhs_angle;
         } else {
           return (lhs - p).GetSquaredNorm() < (rhs - p).GetSquaredNorm();
         }
       });

  vector<Vector2D> stack;
  stack.push_back(P[0]);
  stack.push_back(P[1]);
  for (int i = 2; i < N; ++i) {
    if (stack.size() < 2) {
      stack.push_back(P[i]);
    } else {
      const auto& curr = stack[stack.size() - 1];
      const auto& prev = stack[stack.size() - 2];
      const auto& p = P[i];
      if ((curr - prev).GetCcw(p - curr) > kEpsilon) {
        stack.push_back(p);
      } else {
        stack.pop_back();
        --i;
      }
    }
  }
  return stack.size();
}

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs.
  cin >> N;
  for (int i = 0; i < N; ++i) {
    double x, y;
    cin >> x >> y;
    P.emplace_back(x, y);
  }

  // Solve.
  cout << Solve() << "\n";

  return 0;
}