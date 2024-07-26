#include <iostream>

int N;
int NUMBERS[2000 + 1];
int M;
int S;
int E;
int CACHE[2000 + 1][2000 + 1];  // 0: Not init, 1: False, 2: True.

int Solve(int s, int e) {
  int& ret{CACHE[s][e]};
  if (ret != 0) {
    return ret;
  } else if (s >= e) {
    return (ret = 2);
  } else {
    return (ret =
                (Solve(s + 1, e - 1) == 2) && NUMBERS[s] == NUMBERS[e] ? 2 : 1);
  }
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> N;
  for (auto i{1}; i <= N; ++i) {
    std::cin >> NUMBERS[i];
  }
  std::cin >> M;

  // Solve.
  for (auto i{0}; i < M; ++i) {
    std::cin >> S >> E;
    std::cout << (Solve(S, E) == 2) << "\n";
  }

  return 0;
}
