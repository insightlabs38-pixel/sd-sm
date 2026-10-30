# Track B: Index

A C++20, standard-library-only solution to [Track B](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/b-index.md).

## Approach

Queries are parsed before the corpus. A case-insensitive ASCII token dictionary selects only query-visible terms, with byte-exact comparison and no Unicode normalization. A four-worker corpus scan builds ascending per-term document postings and a compact document-delimited tape of selected term IDs. Four query workers preserve output order. Boolean expressions use sorted-set intersection, union and difference in strict left-to-right order, with rare-term candidate probes and adaptive intersections for unbalanced lists. Phrase queries choose their least-frequent term as a candidate filter and verify exact adjacency around that anchor. High-frequency phrases are deduplicated and evaluated by a shared token-level Aho-Corasick automaton with parallel document-range scans. Output is deterministic and includes the exact 64-bit sum and first ten IDs. Token-byte classification uses a branchless ASCII predicate verified equivalent for every byte value. The corpus scan fuses token fingerprinting with byte traversal, and four query workers claim balanced 64-query batches while preserving output order.

## Validation

Fused token hashing passed seven-seed differential and collision checks, exact full seed-1/2 comparisons, and an offline pinned Docker sample run in [41109851588](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41109851588). Runner measurements are not official board scores; the integration log records current measurements in [PERF.md](PERF.md).

## Dependencies

None beyond the C++ standard library and system C runtime. Build image is the pinned, organizer-allowlisted `gcc:15`; runtime image is the pinned `debian:13-slim`.

## Performance evidence

The measured comparison and source-size tradeoff are documented in [PERF.md](PERF.md). No official board run ID or K score is available yet.
