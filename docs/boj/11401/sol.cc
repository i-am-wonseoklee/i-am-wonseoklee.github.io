#include <cstdint>
#include <iostream>
#include <tuple>

constexpr std::int64_t P{1000000007};
std::int64_t N;
std::int64_t K;

std::tuple<std::int64_t, std::int64_t> GetNumDenom(std::int64_t n,
                                                   std::int64_t k) {
  std::int64_t numerator{1};
  for (int i{1}; i <= n; ++i) {
    numerator *= i;
    numerator %= P;
  }
  std::int64_t denominator{1};
  for (int i{1}; i <= k; ++i) {
    denominator *= i;
    denominator %= P;
  }
  for (int i{1}; i <= n - k; ++i) {
    denominator *= i;
    denominator %= P;
  }
  return {numerator, denominator};
}

std::int64_t GetPow(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  } else {
    auto half{GetPow(base, exponent / 2) % P};
    auto half_sq{(half * half) % P};
    return exponent % 2 == 0 ? half_sq : (half_sq * base) % P;
  }
}

std::int64_t Solve() {
  auto [numerator, denominator] = GetNumDenom(N, K);
  return (numerator * GetPow(denominator, P - 2)) % P;
}

int main(void) {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> N >> K;

  // Solve.
  std::cout << Solve() << std::endl;

  return 0;
}
