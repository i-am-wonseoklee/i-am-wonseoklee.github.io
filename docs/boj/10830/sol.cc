#include <cstdint>
#include <iostream>
#include <vector>

using Mat1D = std::vector<std::int64_t>;
using Mat2D = std::vector<Mat1D>;

int N;
std::int64_t B;
Mat2D A;
Mat2D EYE;
constexpr int kR(1000);

Mat2D Multiply(const Mat2D& mat0, const Mat2D& mat1) {
  Mat2D ret(N, Mat1D(N, 0));
  for (std::size_t r{0}; r < mat0.size(); ++r) {
    for (std::size_t c{0}; c < mat0[r].size(); ++c) {
      for (std::size_t i{0}; i < mat0[r].size(); ++i) {
        ret[r][c] += mat0[r][i] * mat1[i][c];
        ret[r][c] %= kR;
      }
    }
  }
  return ret;
}

Mat2D Solve(std::int64_t exponent) {
  if (exponent == 0) {
    return EYE;
  } else {
    auto half{Solve(exponent / 2)};
    auto half_sq{Multiply(half, half)};
    return exponent % 2 ? Multiply(half_sq, A) : half_sq;
  }
}

int main(void) {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> N >> B;
  A.assign(N, Mat1D(N, 0));
  for (auto r{0}; r < N; ++r) {
    for (auto c{0}; c < N; ++c) {
      std::cin >> A[r][c];
    }
  }

  // Solve.
  EYE.assign(N, Mat1D(N, 0));
  for (auto r{0}; r < N; ++r) {
    EYE[r][r] = 1;
  }
  auto answer{Solve(B)};
  for (auto r{0}; r < N; ++r) {
    for (auto c{0}; c < N; ++c) {
      std::cout << answer[r][c] << ' ';
    }
    std::cout << "\n";
  }

  return 0;
}