# Track C: Join

A byte-oriented C++17 CSV parser reads hostile quoted records, maps region ids through a dense table, and aggregates country statistics. The parallel parser splits work only at valid record boundaries and combines worker-local name tables with exact byte equality. A compact 32-bit name hash reduces table memory while retaining a full collision-safe comparison.

No third-party runtime dependencies. Current correctness, Docker and measured performance evidence is recorded in [PERF.md](PERF.md).
