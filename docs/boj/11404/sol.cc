#include <algorithm>
#include <iostream>

int N;
int M;
int D[100 + 1][100 + 1];
constexpr int kMaxDist{1000000000 + 1};

void Solve() {
  for (auto m{1}; m <= N; ++m) {
    for (auto i{1}; i <= N; ++i) {
      for (auto j{1}; j <= N; ++j) {
        D[i][j] = std::min(D[i][j], D[i][m] + D[m][j]);
      }
    }
  }
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Initialize.
  for (auto i{0}; i < 100 + 1; ++i) {
    for (auto j{0}; j < 100 + 1; ++j) {
      D[i][j] = (i != j) ? kMaxDist : 0;
    }
  }

  // Read inputs.
  std::cin >> N >> M;
  for (auto i{0}; i < M; ++i) {
    int from, to, dist;
    std::cin >> from >> to >> dist;
    D[from][to] = std::min(D[from][to], dist);
  }

  // Solve.
  Solve();

  // Print answer.
  for (auto i{1}; i <= N; ++i) {
    for (auto j{1}; j <= N; ++j) {
      std::cout << ((D[i][j] < kMaxDist) ? D[i][j] : 0) << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;

  return 0;
}