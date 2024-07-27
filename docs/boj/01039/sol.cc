#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int N;
int K;
bool VISIT[10 + 1][1000000 + 1];

int Solve() {
  auto vectorize{[](int n) -> std::vector<int> {
    std::vector<int> digits;
    while (n != 0) {
      digits.push_back(n % 10);
      n /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
  }};

  auto numberize{[](const std::vector<int>& v) -> int {
    auto ret{0};
    auto base{1};
    for (auto it{v.rbegin()}; it != v.rend(); ++it) {
      ret += (*it) * base;
      base *= 10;
    }
    return ret;
  }};

  std::queue<std::pair<int, int>> q;
  VISIT[0][N] = true;
  q.push({0, N});
  while (!q.empty()) {
    auto [k, n] = q.front();
    q.pop();
    auto v{vectorize(n)};
    for (std::size_t i{0}; i + 1 < v.size(); ++i) {
      for (std::size_t j{i + 1}; j < v.size(); ++j) {
        std::swap(v[i], v[j]);
        auto n{numberize(v)};
        if (v[0] != 0 && k + 1 <= K && !VISIT[k + 1][n]) {
          VISIT[k + 1][n] = true;
          q.push({k + 1, n});
        }
        std::swap(v[i], v[j]);
      }
    }
  }

  for (int i{1000000}; i >= 1; --i) {
    if (VISIT[K][i]) {
      return i;
    }
  }
  return -1;
}

int main() {
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