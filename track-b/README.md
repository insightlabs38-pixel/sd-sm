# Track B: Index

A C++20, standard-library-only solution to [Track B](https://github.com/hackathon-raptors/speed-demon-2026/blob/main/specs/b-index.md).

## Approach

Queries select a collision-safe ASCII token dictionary. Full corpora use 6 workers to scan disjoint document ranges with AVX2 byte classification and CRC32C fingerprints with exact packed short keys and full-byte long-token verification. Document-local batches prefetch dictionary probes, whose slots pack term IDs, Boolean columns and phrase heads. Boolean terms populate reusable 1,536-document bitmaps with bounded capacity and rows touched only for terms present in the block; compact plans apply every operator strictly left to right. Population counts compute exact counts and ID sums without materializing answer lists. Phrase queries use sampled rare anchors and verify adjacency against the same exact lookup probes. Sampling changes work selection only. First-ten arrays are allocated only for matching queries. Workers merge count, sum and first-ten summaries in document order. No corpus-wide postings, positions, token tape or phrase automaton is retained.

## Validation

[Pinned production qualification](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41159913998) passes three full seeds, published sample/full hashes, an independent tiny reference, ASan/UBSan, TSan, expanded differential/adversarial oracles and restricted offline Docker. See PERF.md for the complete evidence. Runner measurements are not official board scores.

## Dependencies

None beyond the C++ standard library and system C runtime. Build image is the pinned, organizer-allowlisted `gcc:15`; runtime image is the pinned `debian:13-slim`.

## Official trial

This six-worker candidate from open PR #5 is staged for a controlled official scoring-box run. It remains unpromoted until all board gates pass and its K exceeds the current BEST; the preceding 12-worker source is preserved in the parent release commit for rollback.
