#include <iostream>
#include <queue>
#include <vector>

int N;
std::priority_queue<int, std::vector<int>> LEFT;   // max heap.
std::priority_queue<int, std::vector<int>> RIGHT;  // min heap.

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read input & solve.
  std::cin >> N;
  for (int i{0}; i < N; ++i) {
    int n;
    std::cin >> n;
    if (LEFT.size() == 0) {
      LEFT.push(n);
    } else if (n <= LEFT.top()) {
      RIGHT.push(-LEFT.top());
      LEFT.pop();
      LEFT.push(n);
    } else {
      RIGHT.push(-n);
    }
    // Rebalance.
    if (RIGHT.size() > LEFT.size()) {
      LEFT.push(-RIGHT.top());
      RIGHT.pop();
    }

    std::cout << LEFT.top() << "\n";
  }

  return 0;
}