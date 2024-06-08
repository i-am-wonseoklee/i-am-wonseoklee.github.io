#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// Inputs.
constexpr int kMaxDist = 1'000'000;
int N;
int M;
vector<vector<pair<int, int>>> ADJ;

// Solution.
vector<int> DIST;
vector<int> PREV;
set<int> VERTICES_IN_CYCLE;
vector<bool> VISITED;

bool Bfs(const set<int>& sources, const set<int>& destinatios) {
  VISITED.assign(N, false);
  queue<int> q;
  for (int source : sources) {
    VISITED[source] = true;
    if (destinatios.find(source) != destinatios.end()) {
      return true;
    }
    q.emplace(source);
    while (!q.empty()) {
      const auto& here = q.front();
      q.pop();
      for (const auto& [there, _] : ADJ[here]) {
        if (!VISITED[there]) {
          VISITED[there] = true;
          if (destinatios.find(there) != destinatios.end()) {
            return true;
          }
          q.emplace(there);
        }
      }
    }
  }
  return false;
}

void Solve() {
  DIST[0] = 0;
  PREV[0] = -1;
  int it;
  for (it = 0; it < N; ++it) {
    bool has_relaxed = false;
    for (int u = 0; u < N; ++u) {
      for (const auto& [v, w] : ADJ[u]) {
        if (DIST[u] - w < DIST[v]) {
          has_relaxed = true;
          DIST[v] = DIST[u] - w;
          PREV[v] = u;
          if (it == N - 1) {
            VERTICES_IN_CYCLE.insert(u);
          }
        }
      }
    }
    if (!has_relaxed) {
      break;
    }
  }
  if (!VERTICES_IN_CYCLE.empty() && Bfs({0}, VERTICES_IN_CYCLE) &&
      Bfs(VERTICES_IN_CYCLE, {N - 1})) {
    cout << -1 << endl;
  } else {
    stack<int> path;
    int v = N - 1;
    while (PREV[v] != -1) {
      path.push(v);
      v = PREV[v];
    }
    path.push(v);
    while (!path.empty()) {
      cout << path.top() + 1 << ' ';
      path.pop();
    }
  }
}

int main() {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs.
  cin >> N >> M;
  ADJ.assign(N, {});
  DIST.assign(N, kMaxDist);
  PREV.assign(N, -1);
  for (int it = 0; it < M; ++it) {
    int u, v, w;
    cin >> u >> v >> w;
    ADJ[u - 1].push_back({v - 1, w});
  }

  // Solve.
  Solve();

  return 0;
}