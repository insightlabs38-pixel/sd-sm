#include <algorithm>
#include <cstdio>
#include <numeric>
#include <random>
#include <vector>
int main() {
  unsigned n = 1740512, m = 5000000, main = n - 2;
  std::mt19937 rng(17071);
  std::vector<unsigned> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::shuffle(p.begin(), p.end(), rng);
  FILE *f = fopen("/mnt/champion-train/graph.txt", "w");
  fprintf(f, "%u %u\n", n, m);
  auto edge = [&](unsigned a, unsigned b, unsigned w) {
    fprintf(f, "%u %u %u\n", p[a], p[b], w);
  };
  auto weight = [&] {
    unsigned w = 20 + rng() % 180;
    return rng() % 20 ? w : w * 8;
  };
  for (unsigned i = 0; i < main; ++i) {
    edge(i, (i + 1) % main, weight());
    edge((i + 1) % main, i, weight());
  }
  for (unsigned i = 0; i < (m - 2 * main - 2) / 2; ++i) {
    unsigned a = p[i] % main, b = (a + 1320) % main;
    edge(a, b, weight());
    edge(b, a, weight());
  }
  edge(main, main + 1, ~0u);
  edge(main + 1, main, ~0u);
  fclose(f);
  f = fopen("/mnt/champion-train/queries.txt", "w");
  for (unsigned i = 0; i < 1020; ++i) {
    unsigned a = rng() % main, r = 1u << (rng() % 9),
             b = (a + r + (rng() % r) * 1320) % main;
    fprintf(f, "%u %u\n", p[a], p[b]);
  }
  fprintf(f, "%u %u\n%u %u\n%u %u\n%u %u\n", p[main], p[main + 1], p[main + 1],
          p[main], p[0], p[main], p[1], p[1]);
  fclose(f);
}
