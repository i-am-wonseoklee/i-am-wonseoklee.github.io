#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Inputs.
int T;
double XMIN, YMIN, XMAX, YMAX;
double X1, Y1, X2, Y2;

// Solution.
constexpr double kEpsilon = 1e-7;

class Vector2D {
 public:
  Vector2D() = default;
  Vector2D(double x, double y) : x_(x), y_(y) {}

  double x() const { return x_; }
  double y() const { return y_; }

  double GetNorm() const { return sqrt(GetSquaredNorm()); }
  double GetSquaredNorm() const { return x_ * x_ + y_ * y_; }
  double GetDot(const Vector2D& rhs) const { return x_ * rhs.x_ + y_ * rhs.y_; }
  double GetDet(const Vector2D& rhs) const { return x_ * rhs.y_ - y_ * rhs.x_; }

  Vector2D operator+(const Vector2D& rhs) const {
    return Vector2D(x_ + rhs.x_, y_ + rhs.y_);
  }
  Vector2D operator-(const Vector2D& rhs) const {
    return Vector2D(x_ - rhs.x_, y_ - rhs.y_);
  }
  Vector2D operator*(double scale) const {
    return Vector2D(x_ * scale, y_ * scale);
  }
  bool operator<(const Vector2D& rhs) const {
    if (abs(x_ - rhs.x_) >= kEpsilon) {
      return x_ < rhs.x_;
    }
    return y_ < rhs.y_;
  }
  bool operator<=(const Vector2D& rhs) const {
    return ((*this < rhs) || (*this == rhs));
  }
  bool operator==(const Vector2D& rhs) const {
    return (rhs - *this).GetSquaredNorm() < kEpsilon;
  }
  bool operator!=(const Vector2D& rhs) const { return !(*this == rhs); }

 private:
  double x_;
  double y_;
};

class Segment2D {
 public:
  Segment2D() = default;
  Segment2D(const Vector2D& src, const Vector2D& dst) : src_(src), dst_(dst) {
    if (dst_ < src_) {
      swap(src_, dst_);
    }
  }

  const Vector2D& src() const { return src_; }
  const Vector2D& dst() const { return dst_; }

  Vector2D GetDirection() const { return dst_ - src_; }

  bool IsColinear(const Segment2D& rhs) const {
    return abs(GetDirection().GetDet(rhs.GetDirection())) < kEpsilon;
  }
  bool IsPointOnSegment(const Vector2D& point) const {
    return IsColinear(Segment2D(dst_, point)) && src_ <= point && point <= dst_;
  }
  // Returns the number of intersections between this segment and rhs. If the
  // number of intersections is infinite, returns -1.
  int CountIntersections(const Segment2D& rhs) const {
    const auto dir_0 = GetDirection();
    const auto dir_1 = rhs.GetDirection();
    const auto det = dir_0.GetDet(dir_1);

    if (abs(det) < kEpsilon) {
      if (!IsColinear(Segment2D(dst_, rhs.src())) ||
          (dst_ < rhs.src() || rhs.dst() < src_)) {
        return 0;
      } else if ((src_ == rhs.dst() && dst_ != rhs.src()) ||
                 (src_ != rhs.dst() && dst_ == rhs.src())) {
        return 1;
      } else {
        return -1;
      }
    } else {
      const auto scale = (rhs.src() - src_).GetDet(dir_1) / det;
      const auto p = src_ + dir_0 * scale;
      return IsPointOnSegment(p) && rhs.IsPointOnSegment(p) ? 1 : 0;
    }
  }

 private:
  Vector2D src_;
  Vector2D dst_;
};

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs.
  cin >> T;
  while (T--) {
    cin >> XMIN >> YMIN >> XMAX >> YMAX;
    cin >> X1 >> Y1 >> X2 >> Y2;

    vector<Segment2D> rectangle;
    rectangle.emplace_back(Vector2D(XMIN, YMIN), Vector2D(XMIN, YMAX));
    rectangle.emplace_back(Vector2D(XMIN, YMAX), Vector2D(XMAX, YMAX));
    rectangle.emplace_back(Vector2D(XMAX, YMAX), Vector2D(XMAX, YMIN));
    rectangle.emplace_back(Vector2D(XMAX, YMIN), Vector2D(XMIN, YMIN));

    Segment2D segment(Vector2D(X1, Y1), Vector2D(X2, Y2));

    // Solve.
    int num_of_corners = 0;
    num_of_corners += segment.IsPointOnSegment({XMIN, YMIN}) ? 1 : 0;
    num_of_corners += segment.IsPointOnSegment({XMIN, YMAX}) ? 1 : 0;
    num_of_corners += segment.IsPointOnSegment({XMAX, YMAX}) ? 1 : 0;
    num_of_corners += segment.IsPointOnSegment({XMAX, YMIN}) ? 1 : 0;

    int num_of_intersections = 0;
    for (const auto& side : rectangle) {
      const auto query = segment.CountIntersections(side);
      if (query == -1) {
        num_of_intersections = -1;
        break;
      } else {
        num_of_intersections += query;
      }
    }
    int answer =
        num_of_intersections == -1 ? 4 : num_of_intersections - num_of_corners;
    cout << answer << '\n';
  }

  return 0;
}