# Track C: performance log

Every step from the reference to your final version, each with the live-board run ID that measured it. Judges check that the run IDs exist and that each change moved the way you say it did.

| Step | Change | Run ID | T (s) | M (MB) | Points |
|---|---|---|---|---|---|
| 0 | The reference, unchanged | | 14.44 | 367 | 0 |
| 1 | | | | | |

## Parallel CSV aggregation handoff validation, October 30, 2026

- Promoted developer HEAD `9f68e9f76b9fb4e82a1c2eef6b1d2b335861280b`; the prior official Track C candidate remains in parent history for rollback.
- Board-equivalent offline Docker build passed with an allowlisted image (80 MB). The sandbox full seed-1 output matched the published reference SHA-256 `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536` (2.90 s including container startup; local timing only).
- Independent developer differential suite passed both hostile handwritten CSV cases, tiny seeds 1–3, sample seeds 1–2, and full seed 1 byte-for-byte against its reference; published sample hash `9035fed36823232dd41ae2d1b9d6d21aa7c73f49d8e95647e953a89d5ebe9a66` matched.
- No live board run ID exists; no scoring-box performance or score is claimed.

## Release-context cleanup, October 30, 2026

- Retained the verified C++ joiner from `sd-tc` HEAD `9f68e9f76b9fb4e82a1c2eef6b1d2b335861280b`; removed unused starter Python reference and launcher files from the Docker context. `join.cpp` and its Dockerfile are unchanged from the prior verified promotion.
- The existing official full/sample differential and Docker receipts remain valid for the unchanged executable. No new board run or score is claimed.
