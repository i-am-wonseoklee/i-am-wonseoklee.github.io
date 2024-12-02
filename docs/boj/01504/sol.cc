#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

int N, E;
vector<pair<int, int>> ADJ[800 + 1];
int V1, V2;

// Shortest path using Dijkstra algorithm.
int64_t Sp1(int src, int dst) {
  vector<int> dist(N + 1, numeric_limits<int>::max());
  priority_queue<pair<int, int>> pq;
  dist[src] = 0;
  pq.push({-dist[src], src});
  while (!pq.empty()) {
    auto cost_so_far = -pq.top().first;
    auto here = pq.top().second;
    pq.pop();
    if (dist[here] < cost_so_far) {
      continue;
    }
    dist[here] = cost_so_far;
    if (here == dst) {
      return dist[here];
    }
    for (const auto neighbor : ADJ[here]) {
      auto there = neighbor.first;
      auto cost = neighbor.second;
      if (dist[there] > dist[here] + cost) {
        dist[there] = dist[here] + cost;
        pq.push({-dist[there], there});
      }
    }
  }
  return numeric_limits<int>::max();
}

int main() {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> N >> E;
  for (int i = 0; i < E; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    ADJ[a].push_back({b, c});
    ADJ[b].push_back({a, c});
  }
  cin >> V1 >> V2;

  // Solve the problem.
  auto v1_to_v2 = Sp1(V1, V2);
  auto ans = min(Sp1(1, V1) + v1_to_v2 + Sp1(V2, N),
                 Sp1(1, V2) + v1_to_v2 + Sp1(V1, N));
  if (ans >= numeric_limits<int>::max()) {
    cout << -1 << '\n';
  } else {
    cout << ans << '\n';
  }

  return 0;
}