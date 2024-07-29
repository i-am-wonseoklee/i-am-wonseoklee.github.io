#include <iostream>
#include <queue>
#include <string>
#include <vector>

int H, W;
std::string MAP[100];
bool VISIT[100][100][4];

struct State {
  int row;
  int col;
  int dir;
  int mirrors;
};

int Solve() {
  auto find_src_dst{[]() -> std::pair<int, int> {
    int src{-1};
    int dst{-1};
    for (auto r{0}; r < H; ++r) {
      for (auto c{0}; c < W; ++c) {
        if (MAP[r][c] == 'C') {
          src = src == -1 ? r * W + c : src;
          dst = src != -1 ? r * W + c : dst;
        }
      }
    }
    return {src, dst};
  }};

  auto is_visitable{[](int row, int col, int dir) -> bool {
    return 0 <= row && row < H && 0 <= col && col < W && MAP[row][col] != '*' &&
           !VISIT[row][col][dir];
  }};

  auto [src, dst]{find_src_dst()};
  auto src_r{src / W};
  auto src_c{src % W};
  auto dst_r{dst / W};
  auto dst_c{dst % W};
  std::queue<State> q;
  for (auto d{0}; d < 4; ++d) {
    VISIT[src_r][src_c][d] = true;
    q.push({src_r, src_c, d, 0});
  }

  const int dr[4]{1, 0, -1, 0};
  const int dc[4]{0, -1, 0, 1};
  while (!q.empty()) {
    auto state{q.front()};
    q.pop();

    if (state.row == dst_r && state.col == dst_c) {
      return state.mirrors;
    }

    int ndir;
    int nr;
    int nc;

    // Keep direction.
    for (auto i{1};; ++i) {
      ndir = state.dir;
      nr = state.row + i * dr[ndir];
      nc = state.col + i * dc[ndir];
      if (is_visitable(nr, nc, ndir)) {
        VISIT[nr][nc][ndir] = true;
        q.push({nr, nc, ndir, state.mirrors});
      } else {
        break;
      }
    }

    if (MAP[state.row][state.col] == 'C') {
      continue;
    }

    // `/`.
    if (state.dir == 0) {
      ndir = 1;
    } else if (state.dir == 1) {
      ndir = 0;
    } else if (state.dir == 2) {
      ndir = 3;
    } else {
      ndir = 2;
    }
    for (auto i{1};; ++i) {
      nr = state.row + i * dr[ndir];
      nc = state.col + i * dc[ndir];
      if (is_visitable(nr, nc, ndir)) {
        VISIT[nr][nc][ndir] = true;
        q.push({nr, nc, ndir, state.mirrors + 1});
      } else {
        break;
      }
    }

    // `\`.
    if (state.dir == 0) {
      ndir = 3;
    } else if (state.dir == 1) {
      ndir = 2;
    } else if (state.dir == 2) {
      ndir = 1;
    } else {
      ndir = 0;
    }
    for (auto i{1};; ++i) {
      nr = state.row + i * dr[ndir];
      nc = state.col + i * dc[ndir];
      if (is_visitable(nr, nc, ndir)) {
        VISIT[nr][nc][ndir] = true;
        q.push({nr, nc, ndir, state.mirrors + 1});
      } else {
        break;
      }
    }
  }

  return -1;
}

int main() {
  // For faster IO.
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  // Read inputs.
  std::cin >> W >> H;
  for (auto i{0}; i < H; ++i) {
    std::cin >> MAP[i];
  }

  // Solve.
  std::cout << Solve() << std::endl;

  return 0;
}