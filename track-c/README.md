# Track C: Join

A byte-oriented C++17 CSV parser handles quoted fields, maps region IDs through a dense table, and aggregates country statistics. Each worker batches parsed records and builds a compact exact-name table. Interned names are copied into worker-owned arenas so consumed mmap pages can be reclaimed safely; merge partitions names into independent hash shards and retains exact byte equality after hash matches.

The source passed the full seed-1 exact-output hash, adversarial megabyte quoted-name lifetime checks, and a pinned offline Docker run as an unprivileged user with a read-only root filesystem in [CI run 41117768919](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41117768919). The build uses the pinned, allowlisted GCC image with `-march=x86-64-v3`. There are no third-party runtime dependencies.

Performance measurements and the memory/runtime tradeoff between worker counts are recorded in [PERF.md](PERF.md). CI and local measurements are not official board scores.
