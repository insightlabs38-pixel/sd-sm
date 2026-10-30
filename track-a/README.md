# Track A: Ingest

Dependency-free C++20 implementation of the [Speed Demon 2026 Track A specification](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/a-ingest.md).

## Approach

Five newline-aligned mmap partitions are parsed concurrently. Each worker uses a compact endpoint dictionary using sampled SSE4.2 CRC32 fingerprints, with exact byte comparison on every hash match and exact per-hour counters, then emits packed group/latency records. The endpoint boundary scan uses bounded `memchr`. After workers join, endpoint IDs are reconciled by full-string equality, counts are merged, and latencies are scattered into contiguous group spans. Four output workers independently compute exact nearest-rank percentiles and serialize disjoint hour ranges in deterministic byte order.

## Dependencies

No third-party runtime libraries. Build with C++20, pthreads and the pinned Docker toolchain. The default input is `/data/requests.log`, and the only output is `/out/summary.txt`. `SD_DATA_DIR` and `SD_OUT_DIR` optionally override these directories for local testing.

## Performance evidence

The latest developer exactness and sandbox run is [41096594772](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41096594772). Local synthetic worker-scaling measurements and official integration evidence are recorded in [PERF.md](PERF.md); local timings are not board scores.
