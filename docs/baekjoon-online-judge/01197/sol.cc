#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Inputs.
int V;
int E;
struct Edge {
  int src;
  int dst;
  int weight;
  bool operator<(const Edge& rhs) const { return weight < rhs.weight; }
};
std::vector<Edge> EDGES;

// Solution.
std::vector<int> PARENT;

int Find(int n) {
  if (PARENT[n] == -1) {
    return n;
  } else {
    return (PARENT[n] = Find(PARENT[n]));
  }
}

void Union(int a, int b) { PARENT[Find(a)] = Find(b); }

int64_t Solve() {
  PARENT.assign(V + 1, -1);
  sort(EDGES.begin(), EDGES.end());

  int64_t cost = 0;
  for (const auto& edge : EDGES) {
    if (Find(edge.src) != Find(edge.dst)) {
      Union(edge.src, edge.dst);
      cost += edge.weight;
    }
  }

  return cost;
}

int main(void) {
  // For faster IO.
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Read inputs.
  cin >> V >> E;
  EDGES.resize(E);
  for (int i = 0; i < E; ++i) {
    cin >> EDGES[i].src >> EDGES[i].dst >> EDGES[i].weight;
  }

  // Solve.
  cout << Solve() << "\n";

  return 0;
}