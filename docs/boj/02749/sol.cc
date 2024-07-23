#include <array>
#include <cstdint>
#include <iostream>

using Mat2D = std::array<std::array<std::int64_t, 2>, 2>;

std::int64_t N;
const std::int64_t R{1000000};
const Mat2D M{{{1, 1}, {1, 0}}};
const Mat2D I{{{1, 0}, {0, 1}}};

Mat2D Multiply(const Mat2D& m0, const Mat2D& m1) {
  return Mat2D{{
      {(m0[0][0] * m1[0][0] + m0[0][1] * m1[1][0]) % R,
       (m0[0][0] * m1[0][1] + m0[0][1] * m1[1][1]) % R},
      {(m0[1][0] * m1[0][0] + m0[1][1] * m1[1][0]) % R,
       (m0[1][0] * m1[0][1] + m0[1][1] * m1[1][1]) % R},
  }};
}

Mat2D GetPowerOfM(std::int64_t x) {
  if (x == 0) {
    return I;
  }
  auto half{GetPowerOfM(x / 2)};
  auto half_sq{Multiply(half, half)};
  return x % 2 ? Multiply(half_sq, M) : half_sq;
}

int64_t Solve(std::int64_t n) {
  return n < 2 ? n : GetPowerOfM(n - 1)[0][0];
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read input.
  std::cin >> N;

  // Solve.
  std::cout << Solve(N) << std::endl;

  return 0;
}
