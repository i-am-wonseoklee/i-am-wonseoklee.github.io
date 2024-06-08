#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int TC;
int L, N;

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> TC;
  while (TC--) {
    int shortest = 0;
    int longest = 0;
    cin >> L >> N;
    while (N--) {
      int pos;
      cin >> pos;
      shortest = max(shortest, min(pos, L - pos));
      longest = max(longest, max(pos, L - pos));
    }
    cout << shortest << ' ' << longest << '\n';
  }

  return 0;
}
