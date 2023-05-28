#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Inputs.
int N, M, K;
vector<vector<pair<int, int>>> ADJ;

// Solution.
vector<vector<int64_t>> DIST;

int64_t Solve(void) {
  // Initialize data structures.
  // DIST[i][j] = minimum distance to `i` using `j` paved roads.
  DIST.resize(N + 1, vector<int64_t>(K + 1, numeric_limits<int64_t>::max()));

  // Declare a min heap.
  using Element = pair<int64_t, pair<int, int>>;
  priority_queue<Element, vector<Element>, greater<Element>> pq;

  DIST[1][0] = 0;
  pq.emplace(DIST[1][0], make_pair(1, 0));
  while (!pq.empty()) {
    const auto dist = pq.top().first;
    const auto here = pq.top().second.first;
    const auto paved = pq.top().second.second;
    pq.pop();

    if (DIST[here][paved] < dist) {
      continue;
    } else {
      for (const auto& edge : ADJ[here]) {
        const auto& there = edge.first;
        const auto& weight = edge.second;
        // Consider not paving the road.
        if (dist + weight < DIST[there][paved]) {
          DIST[there][paved] = dist + weight;
          pq.emplace(DIST[there][paved], make_pair(there, paved));
        }
        // COnsider paving the road.
        if (paved < K && dist < DIST[there][paved + 1]) {
          DIST[there][paved + 1] = dist;
          pq.emplace(DIST[there][paved + 1], make_pair(there, paved + 1));
        }
      }
    }
  }

  int64_t answer = numeric_limits<int64_t>::max();
  for (int i = 0; i <= K; ++i) {
    answer = min(answer, DIST[N][i]);
  }

  return answer;
}

int main(void) {
  // For faster input.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> N >> M >> K;
  ADJ.resize(N + 1);
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    ADJ[u].emplace_back(v, w);
    ADJ[v].emplace_back(u, w);
  }

  // Print the answer.
  cout << Solve() << endl;

  return 0;
}
