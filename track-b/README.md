# Track B: Index

A C++20, standard-library-only solution to [Track B](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/b-index.md).

## Approach

Queries are parsed before the corpus. A case-insensitive ASCII token dictionary selects only query-visible terms, with byte-exact comparison and no Unicode normalization. A four-worker corpus scan builds ascending per-term document postings and a compact document-delimited tape of selected term IDs. Four query workers preserve output order. Boolean expressions use sorted-set intersection, union and difference in strict left-to-right order, with rare-term candidate probes and adaptive intersections for unbalanced lists. Phrase queries choose their least-frequent term as a candidate filter and verify exact adjacency around that anchor. High-frequency phrases are deduplicated and evaluated by a shared token-level Aho-Corasick automaton with parallel document-range scans. Output is deterministic and includes the exact 64-bit sum and first ten IDs.

## Validation

The combined full-seed workflows [41093166652](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41093166652) and [41094072407](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41094072407) passed differential oracles, exact full-seed-1/2 outputs and pinned offline Docker execution. The current source passed [exactness/Docker run 41095024159](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41095024159) and [parallel sanitizer run 41094997130](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41094997130). Runner measurements are not official board scores.

## Dependencies

None beyond the C++ standard library and system C runtime. Build image is the pinned, organizer-allowlisted `gcc:15`; runtime image is the pinned `debian:13-slim`.

## Performance evidence

The measured comparison and source-size tradeoff are documented in [PERF.md](PERF.md). No official board run ID or K score is available yet.
