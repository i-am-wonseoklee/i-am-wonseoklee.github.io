#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

constexpr size_t MAX_V = 100'000;

// Inputs.
int V;
vector<pair<int, int>> ADJ[MAX_V + 1];

// Solution.
vector<int64_t> DIST_PASS_1(MAX_V + 1, -1);
vector<int64_t> DIST_PASS_2(MAX_V + 1, -1);

void DoBfs(int src, vector<int64_t>& dist) {
  queue<int> q;
  dist[src] = 0;
  q.push(src);

  while (!q.empty()) {
    auto here = q.front();
    q.pop();
    for (const auto& edge : ADJ[here]) {
      const auto there = edge.first;
      const auto weight = edge.second;
      if (dist[there] == -1) {
        dist[there] = dist[here] + weight;
        q.push(there);
      }
    }
  }
}

int64_t Solve() {
  DoBfs(1, DIST_PASS_1);

  int64_t max_dist = -1;
  int max_idx = -1;
  for (int i = 1; i <= V; ++i) {
    if (DIST_PASS_1[i] > max_dist) {
      max_dist = DIST_PASS_1[i];
      max_idx = i;
    }
  }

  DoBfs(max_idx, DIST_PASS_2);

  max_dist = -1;
  for (int i = 1; i <= V; ++i) {
    if (DIST_PASS_2[i] > max_dist) {
      max_dist = DIST_PASS_2[i];
    }
  }

  return max_dist;
}

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> V;
  for (int i = 1; i <= V; ++i) {
    int here;
    cin >> here;
    while (true) {
      int there;
      cin >> there;
      if (there == -1) {
        break;
      } else {
        int weight;
        cin >> weight;
        ADJ[here].emplace_back(there, weight);
      }
    }
  }

  // Solve.
  cout << Solve() << "\n";

  return 0;
}