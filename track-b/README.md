# Track B: Index

A C++20, standard-library-only solution to [Track B](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/b-index.md).

## Approach

Queries are parsed before the corpus. A collision-safe ASCII token dictionary retains only query-visible terms. Four workers scan disjoint document ranges. Boolean membership is accumulated in sparse 2,048-document bitmaps and evaluated left-to-right; phrase queries use a sampled rare-term anchor, then verify exact adjacent tokens while each document is in memory. The scan keeps neither a corpus-wide postings index nor a corpus-wide token tape. Workers reduce count, 64-bit ID sum, and the first ten IDs in document order, preserving query output order.

## Validation

The three-seed qualification [CI 41157659217](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41157659217) passed the published full seed-1 hash, independent full seed-2/3 Python references, randomized and adversarial differential tests, deliberate CRC32C collision cases, tiny/sample hashes, and pinned offline Docker. Three interleaved Docker measurements per seed gave runner-local median times of 0.579/0.573/0.575 s versus 0.677/0.671/0.668 s for the preceding streaming candidate; candidate peak memory was about 43 MiB. These are developer-runner measurements, not official board scores. See PERF.md for official results when available.

## Dependencies

None beyond the C++ standard library and system C runtime. Build image is the pinned, organizer-allowlisted `gcc:15`; runtime image is the pinned `debian:13-slim`.

## Further work

Use official board evidence to assess this candidate against the prior champion, then tune bounded scan and bitmap costs only when exact multi-seed tests and the full score coefficient justify the change.
