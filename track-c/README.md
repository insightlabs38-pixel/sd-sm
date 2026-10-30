# Track C: Join

A byte-oriented C++17 parser handles hostile quoted CSV, maps region ids through a dense table, and aggregates country statistics. Each worker batches 16 parsed records and builds a compact exact-name table. The merge partitions names into independent hash shards and retains exact byte equality after hash matches.

No third-party runtime dependencies. The integrated source passed full-scale exactness and Docker checks in [CI run 41109853738](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41109853738). Performance evidence and the later rejected merge experiment are recorded in [PERF.md](PERF.md); CI and local figures are not board scores.
