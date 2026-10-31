# Track C: Join

A byte-oriented C++17 parser handles hostile quoted CSV, maps region ids through a dense table, and aggregates country statistics. Six workers parse byte ranges and share an exact-name dictionary with 64-byte-aligned slots: names up to 16 bytes are stored inline and longer names use the arena. Hash matches are confirmed by exact byte equality.

No third-party runtime dependencies. The integrated source passed full-scale exactness and Docker checks in [CI run 41109853738](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41109853738). Performance evidence and the later rejected merge experiment are recorded in [PERF.md](PERF.md); CI and local figures are not board scores.
