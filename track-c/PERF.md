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

## Packed name-table slot promotion, October 30, 2026

- Candidate `sd-tc` main HEAD `c89d755bbb361a5a15764e8d3c9fd9a5f5b76913`, source blob `e897a2cd91853dddb0212a60246b329654c8531e`; rollback is the prior official Track C source in release parent `00838f7`.
- Latest exactness and restricted Docker run [41099550287](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41099550287) passed. Five interleaved local full seed-1 runs matched output SHA-256 `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536`; prior official median 1.2951 s / 250,408 KiB sampled VmHWM, candidate 0.9451 s / 239,628 KiB. Runtime samples were noisy (candidate range 0.915–2.18 s); this is local-host evidence, not scoring hardware.
- Candidate reduces each name-table slot from 32 to 24 bytes with exact equality retained and no new runtime dependencies. No official board run ID or score is available.

## Batched parsing and sharded exact-name merge, October 30, 2026

- Candidate source introduced at `sd-tc` commit `351877510b397b8e2224884e54497d3b877f53c1`, source blob `bdf2a15bc53d541b550536d292e43fc729575dbf`. Current developer HEAD `7eb4ec463341151757d93c37d089fbd8aed3cdff` restores this same source blob after the rejected `8613c07` trial. The previous official release `1c235c35cc93ea146cf794254eecd56fab8f9948` is the rollback point.
- Source-identical CI [41109853738](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41109853738) passed tiny/sample/full differential and exact-output checks plus restricted offline Docker execution; latest-head CI [41115046701](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41115046701) is requalifying the restored blob. Its five paired full-input medians were 0.32 s to 0.30 s; peak RSS was 249,820 to 249,784 KiB. GitHub runner measurements, not board T/M.
- Independently, six interleaved local full seed-1 runs using the official generic compile flags matched the published SHA `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536` for both the prior official and current sources. On this three-CPU host, medians were 1.1074 to 0.8111 s (26.8% lower) and sampled process VmHWM 239,628 to 247,428 KiB (+3.3%). Timing ranges were 0.886–1.228 s and 0.615–0.917 s; these local values are not scoring-box results.
- The current parser batches 16 records and parallelizes exact name reconciliation by hash shard. Source adds 41 physical lines versus the previous official version; runtime dependencies remain zero.
- The developer Dockerfile enables `-march=x86-64-v3`; a seven-run local comparison found no reliable gain over the official generic flags (median 0.9194 s v3 vs 0.9034 s generic, with one large v3 outlier). Kept the official generic Dockerfile. The current candidate compiled with those generic flags and matched the full hash locally; current-head Docker CI used the developer Dockerfile.
- Official board BEST/LATEST: unavailable; the team has no registration entry and no board run IDs exist. No official score is claimed.

## Rejected redundant-scan reduction, October 30, 2026

- Developer head `8613c0784fce55bad2885fe50ea1e11193d6364d` passed exactness and Docker gates in CI [41114839518](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41114839518), but was not promoted. Five paired full-run medians against the experiment baseline `335c0626`: both 0.21 s; peak RSS rose from 250,000 to 259,276 KiB (+3.7%) after adding 18 physical source lines. It shows no measured runtime gain and a memory increase.
- The integrated C champion remains source blob `bdf2a15bc53d541b550536d292e43fc729575dbf`. Developer CI evidence is not an official board run.
