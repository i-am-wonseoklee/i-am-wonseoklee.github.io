#include <algorithm>
#include <iostream>

using namespace std;

int N;
int K;
int WS[100];
int VS[100];
int CACHE[100][100000 + 1];

int Solve() {
  for (int w{WS[0]}; w <= K; ++w) {
    CACHE[0][w] = VS[0];
  }
  for (int i{1}; i < N; ++i) {
    for (int w{0}; w <= K; ++w) {
      CACHE[i][w] = (w - WS[i] >= 0) ? std::max(CACHE[i - 1][w - WS[i]] + VS[i],
                                                CACHE[i - 1][w])
                                     : CACHE[i - 1][w];
    }
  }
  return CACHE[N - 1][K];
}

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> N >> K;
  for (auto i{0}; i < N; ++i) {
    cin >> WS[i] >> VS[i];
  }

  // Solve.
  cout << Solve() << endl;

  return 0;
}
