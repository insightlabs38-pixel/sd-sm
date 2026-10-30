# Track B: Index

A C++20, standard-library-only solution to [Track B](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/b-index.md).

## Approach

Queries are parsed before the corpus. A case-insensitive ASCII token dictionary selects only query-visible terms, with byte-exact comparison and no Unicode normalization. A single corpus scan builds ascending per-term document postings and a compact document-delimited tape of selected term IDs. Boolean expressions use sorted-set intersection, union and difference in strict left-to-right order. Phrase queries normally choose their least-frequent term as a candidate filter and verify exact consecutive token IDs in each candidate document. High-frequency phrases are deduplicated and evaluated by a shared token-level Aho-Corasick automaton over the compact tape, avoiding repeated scans. Corpus indexing uses four workers and merges byte ranges in document order. Large query batches are evaluated in four workers and emitted in original order. Output includes the exact 64-bit sum and first ten IDs.

## Validation

The [public exactness workflow](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41081539702) passed the organizer's published seed-1 `sample` and `full` SHA-256 hashes, byte-for-byte comparisons with the Python reference on sample seeds 2 and 3, seven randomized differential seeds, and an offline pinned Docker build run as uid 65534 on a read-only root filesystem. Local AddressSanitizer/UndefinedBehaviorSanitizer and a separate 1,200-document common-phrase automaton oracle also passed. The workflow's timings are not official board measurements.

## Dependencies

None beyond the C++ standard library and system C runtime. Build image is the pinned, organizer-allowlisted `gcc:15`; runtime image is the pinned `debian:13-slim`.

## Performance evidence

The paired two-seed query evaluation comparison is documented in [PERF.md](PERF.md) and developer workflow [41090220430](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41090220430). It showed 26–31% lower full-seed runtime with similar peak RSS. These are GitHub-runner measurements, not official board scores.
