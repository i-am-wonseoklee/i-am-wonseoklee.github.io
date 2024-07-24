#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int N;
std::vector<std::pair<int, int>> M(500, std::pair<int, int>());
std::vector<std::vector<int>> CACHE(500, std::vector<int>(500, -1));

int Solve(int i, int j) {
  if (CACHE[i][j] != -1) {
    return CACHE[i][j];
  } else if (i == j) {
    return (CACHE[i][j] = 0);
  } else {
    CACHE[i][j] = std::numeric_limits<int>::max();
    for (auto k{i}; k < j; ++k) {
      CACHE[i][j] =
          std::min(CACHE[i][j], Solve(i, k) + Solve(k + 1, j) +
                                    M[i].first * M[k].second * M[j].second);
    }
    return CACHE[i][j];
  }
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> N;
  for (auto i{0}; i < N; ++i) {
    std::cin >> M[i].first >> M[i].second;
  }

  // Solve.
  std::cout << Solve(0, N - 1) << std::endl;

  return 0;
}