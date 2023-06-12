#include <cstdint>
#include <iostream>
#include <map>

using namespace std;

constexpr int MAX_N = 500'000;
constexpr int MAX_MACHINE_NO = 1'000'000;

// Inputs.
int N;
int ARR[MAX_N];
int POS[MAX_MACHINE_NO + 1];

// Solution.
int ARR_COPY[MAX_N];

int64_t CountInversion(int s, int e) {
  if (s >= e) {
    return 0;
  }
  int m = (s + e) / 2;
  int64_t inv = CountInversion(s, m) + CountInversion(m + 1, e);
  int offset = s;
  int left = s;
  int right = m + 1;
  while (left <= m && right <= e) {
    if (ARR[left] < ARR[right]) {
      ARR_COPY[offset++] = ARR[left++];
    } else {
      ARR_COPY[offset++] = ARR[right++];
      inv += m - left + 1;
    }
  }
  while (left <= m) {
    ARR_COPY[offset++] = ARR[left++];
  }
  while (right <= e) {
    ARR_COPY[offset++] = ARR[right++];
  }
  for (int i = s; i <= e; ++i) {
    ARR[i] = ARR_COPY[i];
  }
  return inv;
}

int64_t Solve() { return CountInversion(0, N - 1); }

int main() {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs.
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int machine_no;
    cin >> machine_no;
    POS[machine_no] = i;
  }
  for (int i = 0; i < N; ++i) {
    int machine_no;
    cin >> machine_no;
    ARR[i] = POS[machine_no];
  }

  // Solve.
  cout << Solve() << '\n';

  return 0;
}