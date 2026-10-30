# Track C: Join

A byte-oriented C++17 CSV parser reads hostile quoted records, maps region ids through a dense table, and aggregates country statistics. The parallel parser splits work only at valid record boundaries and combines worker-local name tables using 24-byte packed slots, compact hashes, and exact byte equality.

No third-party runtime dependencies. Current correctness, Docker and measured performance evidence is recorded in [PERF.md](PERF.md).
