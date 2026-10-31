# Traverse

Exact directed shortest paths on a road-like graph, built for the end-to-end clock: parse, preprocess, answer, write.

Pipeline, all phases parallel unless noted:

1. `graph.txt` is mmapped and cut at line boundaries per thread. Each thread parses (SWAR integers) straight into bins keyed by the tail's id bucket, so no triple array and no atomics are needed. Pages already parsed are returned with `madvise`.
2. Each bucket becomes a CSR slice in cache-sized scratch (raw ids).
3. Multi-seed BFS regions (atomic claim bitmap) renumber nodes so graph neighbours are close in memory; the forward CSR is gathered in that order and the reverse CSR is derived from it. Random relabeling in the input otherwise makes every distance access a cache miss.
4. Edges are 4 bytes: node id in the high bits, weight in the low bits. Weights that do not fit store an all-ones marker and are resolved from a sorted escape table, so any 32-bit weight stays exact.
5. Queries run on independent workers in order of source id. Each runs an exact forward probe (256 settles) and then bidirectional Dijkstra with an exact-key bucket queue (4096 buckets, binary-heap overflow for larger jumps). Labels live in 512-node pages allocated on first write and recycled per query, so worker memory follows the search, not `n`.

No third-party runtime dependencies. `SD_THREADS` and `SD_PROBE` select thread count and probe length for validation.

Next: a thread pool for the short phases, balanced BFS regions, and 8-byte bins to lower the build-time memory peak.
