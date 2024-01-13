#include <iostream>
#include <vector>

using namespace std;

int N;
int S;
int ARR[100'000];

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> N >> S;
  for (int i{0}; i < N; ++i) {
    cin >> ARR[i];
  }

  // Solve.
  int answer{N + 1};
  int sum{ARR[0]};
  int s{0}, e{0};
  while (e < N) {
    if (sum < S) {
      sum += ARR[++e];
    } else {
      answer = min(answer, e - s + 1);
      sum -= ARR[s++];
    }
  }

  // Print answers.
  cout << (answer == N + 1 ? 0 : answer) << '\n';

  return 0;
}
