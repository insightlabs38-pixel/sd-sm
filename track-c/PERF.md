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

## Verified name-merge optimization, October 30, 2026

- Promoted `sd-tc` main HEAD `e9bf1ba96f9e1f81c53f617d000bbc94e41de46b`, source blob `28862db57e4a43f52245c4fa44bbf006182b8781`. The preceding official C candidate remains in parent release HEAD `5f9e356c43e9ad613b75dd0a5c6b6c0376f2e39d` for rollback.
- Six alternating native runs on generated official full seed 1 matched the published SHA-256 `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536` for both versions. Prior candidate median 1.0598 s and sampled peak RSS 276,548 KiB; promoted candidate median 0.9382 s and 259,492 KiB (about 11.5% faster and 6.2% lower sampled RSS on this host).
- GitHub Actions run [41089782542](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41089782542) passed tiny/sample/full differential cases, the pinned offline Docker build, sandbox execution and full official hash.
- These local/CI measurements are not board scores. No official board run ID or K is claimed.

## Compact collision-safe name hashes, October 30, 2026

- Integrated `sd-tc` main HEAD `41fa2ed2310dbe0c9356451a8f274b74fca99616`, production source blob `2ede0796ef42bb12be160b9f001ffd7b758024ea`. The implementation retains exact byte comparison after compact 32-bit hash matches. The prior verified source remains in official commit `b7607a7` for rollback.
- GitHub Actions correctness/container run [41090535541](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41090535541) passed tiny, sample, full and differential outputs, the full-seed-1 published hash `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536`, and the pinned offline Docker gate. Follow-up adversarial quote-boundary/colliding-name run [41090872193](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41090872193) passed on current main.
- Paired five-run developer measurements versus the exact-name prior version had equal median runtime (0.34 s) and lower median peak RSS, 255,192 to 251,648 KiB (1.4%). The run did not show a runtime gain; the compact hash is retained for the measured memory reduction with collision-safe equality. These measurements are not board results.
- No live board run ID or K score exists.
