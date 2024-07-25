#include <algorithm>
#include <cstdint>
#include <iostream>

int N;
int M;
std::int64_t U[100 + 1];
std::int64_t C[100 + 1];
std::int64_t CACHE[100 + 1][100 * 100 + 1];

std::int64_t Solve() {
  for (auto i{1}; i <= N; ++i) {
    for (auto c{0}; c < 100 * N + 1; ++c) {
      CACHE[i][c] = CACHE[i - 1][c];
      if (c - C[i] >= 0) {
        CACHE[i][c] = std::max(CACHE[i][c], CACHE[i - 1][c - C[i]] + U[i]);
      }
    }
  }

  auto c{0};
  for (; c < 100 * N + 1; ++c) {
    if (CACHE[N][c] >= M) {
      break;
    }
  }

  return c;
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> N >> M;
  for (auto i{1}; i <= N; ++i) {
    std::cin >> U[i];
  }
  for (auto i{1}; i <= N; ++i) {
    std::cin >> C[i];
  }

  // Solve.
  std::cout << Solve() << std::endl;

  return 0;
}