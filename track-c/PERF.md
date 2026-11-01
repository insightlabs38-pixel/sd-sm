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

## Integrator qualification: streaming page reclamation and owned name arenas (October 30, 2026)

- Imported developer `sd-tc` HEAD `84a75a23a6d9f3f840c35bd5b00be9944656d255`, production source blob `91cd5842426fc8dfd9d8a924e7f72f93f244b572`. Latest source changes were followed by corrected megabyte quoted-name/arena-lifetime tests. CI `41117768919` passed, including full seed-1 expected SHA-256 (`d8088b1c…12a0f536`), pinned offline Docker, unprivileged/read-only sandbox, and single-output-file check.
- Five paired full-run trials in CI `41117096779` comparing the pre-reclamation source to the arena/page-reclamation candidate reduced peak RSS from about 249,800 KiB to 59,600 KiB; elapsed time moved from 0.26 s to 0.22–0.24 s. The candidate owns interned names before discarding consumed mmap pages; note bytes are consumed within the parsed batch before reclaim. This is runner-local evidence, not official-board performance.
- CI `41117431767` compared six to three parser workers on the reclamation candidate: five paired full runs were about 0.22 s / 59,600 KiB versus 0.21 s / 37,400 KiB. The wider 5-run phase profile measured 3 workers at 212.3 ms and 37,744 KiB versus 4 workers at 202.6 ms and 45,236 KiB; three workers trade roughly 5% time for lower memory. Full output stayed byte-exact. `41117745508` failed on an incorrectly escaped test fixture; corrected fixture commit passed in `41117768919`.
- BEST/LATEST official board result: none; no board score or run ID is claimed. Parent submission commit `34dee9b16ab17362b12e75289151a0a9750b2cb8` preserves the previous candidate.

## Champion reconciliation — October 30, 2026

- Restored the board-best source from `34dee9b` (blob `bdf2a15bc53d541b550536d292e43fc729575dbf`), with its matching build recipe and README. It produced actual board K=11.907003, while the newer page-reclamation source at `647f752` produced K=10.989252. This preserves the measured best candidate for the frozen submission.
- Developer `main` HEAD `64155450435a2140e76cf7cd3e1b8f6dd4c31a0f`, source blob `0c0a214316a0dd4ba0e6d6ed81522c572930c25d`, is source-identical to CI-tested commit `8980c770`; full-output, Docker and correctness checks passed in [41138936609]. The matched two-worker four-shard run measured the same 0.26 s median as its two-worker six-shard baseline and reduced RSS 30,152 to 28,900 KiB. Its worker profile was 2 workers: 247.787 ms / 28,968 KiB, 3 workers: 242.042 ms / 36,336 KiB. Estimated from the latest official baseline, T≈0.194 s, M≈27.4 MB, S≈522, D=1, K≈11.45, still below the board-best K=11.907; do not promote.

## Official board receipts — raw-feed snapshot 2026-10-30 22:52:25 UTC

HighVelocity (`highvelocity-7f330e`) is registered. The watcher reported submission HEAD `3059e71b54cd02e920e995d186a369b4be9c0aeb`, healthy, with no queued or in-flight run at this snapshot. BEST and LATEST are both this successful live-board run; build, check, correctness, sandbox, and timeout gates all passed. These are board IDs, not CI IDs. Earlier “no board run/registration” notes are historical and superseded here.

- **BEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.


## Official board receipts — raw-feed snapshot 2026-10-30 22:58:54 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher was healthy at `40847ba5fde8714895533f7b47ce8fee48baa09e`, and the dispatch queue was idle after scoring. All five gates (build, check, correctness, sandbox, timeout) passed; failure was null. BEST and LATEST below are the board's records at this snapshot. These board run IDs are distinct from GitHub Actions IDs.

- **BEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-25971e2e7bf8`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=0.138652 s, M=50,888,704 bytes, S=469, D=1, K=12.159934, points=54.246560.


## Official board results — raw-feed snapshot 2026-10-30 23:10:48 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. The watcher was healthy at `01d4852e1271d5bec3d6de9aaa7641f8616730cb` with an idle queue. Both records passed build, check, correctness, sandbox, and timeout gates; failure was null. These are live-board measurements; BEST and LATEST are separately reported, and run IDs are not GitHub Actions IDs.

- **BEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-2852f06b54d2`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.151174 s, M=51,224,576 bytes, S=469, D=1, K=11.630123, points=53.279216.


## Official board results — raw-feed snapshot 2026-10-31 00:12:03 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. Watcher was healthy at `157f1d478136fd0d7950aa2a82e121c087ec7ec7`, with no queued or in-flight run. Every gate passed; failure was null. These are board measurements, and BEST/LATEST are tracked separately. Board run IDs are not GitHub Actions IDs.

- **BEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-c780a5a2007f`; commit `157f1d478136fd0d7950aa2a82e121c087ec7ec7`; T=0.137002 s, M=50,987,008 bytes, S=469, D=1, K=12.228219, points=54.368160.


## Official board results — raw-feed snapshot 2026-10-31 00:17:27 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`, queue idle. All five gates passed and failure was null. BEST and LATEST are reported separately; these are live-board IDs, not GitHub Actions IDs.

- **BEST:** `run-b7259ab42416`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-383872c272e3`; commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.141475 s, M=51,986,432 bytes, S=469, D=1, K=11.986729, points=53.935035.


## Verified `sd-tc` main candidate evaluated against the official source — October 31, 2026

- Imported developer HEAD `d6ec5b0c6a1e517032e53a2c843a264363ac94a8`, source blob `804516b935b4f544d7895291dc433de3e225b08c`. CI [41145051410](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41145051410) passed tiny/sample adversarial cases, official seed-1 full output, and restricted offline Docker. A separate paired 13-run full seed-1 local comparison against the official source matched the published hash each run: T median 0.687834 to 0.469036 s; process-sampled RSS 253,308,928 to 25,833,472 bytes. Because mmap page accounting differs across hosts, RSS is local evidence and is excluded from the conservative K estimate.
- Pinned clang-format 23.1.3 and scc 4.1.0 measured S=469 for the board source and S=523 for this candidate; D remains 1. Using the local T ratio (0.6819), holding official board M unchanged, and applying the frozen formula to board BEST K=12.246449 gives conservative estimated K≈14.59. CI full-scale comparison also showed about 0.15 s / 28 MB versus 0.16–0.17 s / 30 MB against its prior development source. Actual evaluation at `run-5f056bda0a59` scored K=10.070529 and failed the score comparison despite passing all gates; the candidate was rolled back. The restored champion source was re-evaluated at `run-808df80f1ac7`; see the latest raw-feed receipt below.


## Official board results — raw feed, 2026-10-31 00:23:55 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `73d8cecee9e50825a4f416b77c11fec448955782`; queue idle. All five gates passed for BEST and LATEST; failure was null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-5f056bda0a59`, commit `73d8cecee9e50825a4f416b77c11fec448955782`; T=0.259085 s, M=25,219,072 bytes, S=523, D=1, K=10.070529, points=50.152613.

The imported `sd-tc` candidate (`d6ec5b0c6a1e517032e53a2c843a264363ac94a8`) passed correctness and sandbox gates but reduced K by 17.8% versus BEST. It is rolled back here to the source and README at `b8e6540`; rollback is also available in official Git history.


## Official board results — raw feed observed 2026-10-31 00:29:07 UTC

Watcher was healthy at `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca` (last checked 00:28:14 UTC); queue idle. All five gates passed; failure was null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-808df80f1ac7`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.137847 s, M=50,483,200 bytes, S=469, D=1, K=12.214917, points=54.344526. The C source in this commit is the restored prior champion.


## New `sd-tc/main` challenger staged for official scoring — October 31, 2026

- Candidate developer HEAD `ab3789b9657a2a6e7609f5ef166278bb8c1e2a57`, source blob `e8baeb7ae5f6158ab159ff48ddc2a03d902c0112`; it adds a two-worker exact name/group intersection merge to the previously board-rejected mmap candidate. CI [41150626041](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41150626041) passed handwritten and collision/boundary/growth stress, tiny/sample/full-seed reference equality (full SHA `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536`), paired full-scale comparison, and pinned offline Docker.
- Independent interleaved 5-run seed-1 comparison against the current official C source matched that exact hash on every run: local median wall 0.8443 s to 0.7251 s (14.1% lower). Sampled RSS medians were 248,180 KiB and 26,968 KiB, but mmap accounting differs by host. The local source-axis estimate was not reliable: the board measured S=563, not the estimated 522.
- Official result `run-0a1a4e1eb943` passed all gates but measured T=0.247212 s, M=19,025,920 bytes, S=563, D=1, K=10.787339, points=51.645716. Relative to BEST K=12.246449, K fell 11.9%; despite lower measured memory, slower T and larger S made this a losing candidate. The earlier source blob `804516b` also scored lower (K=10.070529). This challenger is rolled back to source and README from parent `8233a64`; no runtime dependencies were added.


## Official board results — raw feed observed 2026-10-31 00:34:36 UTC

Watcher healthy at `8233a6406105e8580d72bc059d91e48eb88e0868`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-accf0948a6f0`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.147599 s, M=51,208,192 bytes, S=469, D=1, K=11.770881, points=53.540448. This was the restored champion source.


## Official board results — raw feed observed 2026-10-31 00:40:29 UTC

Watcher healthy at `b6f184e81a93554f4dd2b2e0284258345964f45f`, queue idle; all five gates passed for each latest run, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-0a1a4e1eb943`, commit `b6f184e81a93554f4dd2b2e0284258345964f45f`; T=0.247212 s, M=19,025,920 bytes, S=563, D=1, K=10.787339, points=51.645716. Source is rolled back in the next integration checkpoint.


## Official board results — raw feed observed 2026-10-31 00:46:16 UTC

Watcher healthy at `94a98da3f2e1de31f3b6fc308194c698f3603249`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-165ce1672090`, commit `94a98da3f2e1de31f3b6fc308194c698f3603249`; T=0.137152 s, M=50,913,280 bytes, S=469, D=1, K=12.225067, points=54.361892. Restored C champion; the prior challenger run `run-0a1a4e1eb943` remains a failed score comparison.


## Official board results — raw feed observed 2026-10-31 00:51:41 UTC

Watcher healthy at `8b137acc1b2f3a83c9b7c422088b7b966357232e`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-5441ca0d1f83`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.140844 s, M=51,834,880 bytes, S=469, D=1, K=12.020567, points=53.996248. The restored champion source is active.


## Official board results — raw feed observed 2026-10-31 01:14:45 UTC

Watcher healthy at `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`, queue idle; all five gates passed, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-8becef12c304`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.139187 s, M=52,109,312 bytes, S=469, D=1, K=12.079144, points=54.101807.


## Official latest board results — raw feed observed 2026-10-31 01:19:37 UTC

Watcher healthy at `266578e73fec11894c067b8b11a0910657a8ccff`, queue idle; all five gates passed for all four tracks, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-af96dab0fcc1`, commit `266578e73fec11894c067b8b11a0910657a8ccff`; T=0.140017 s, M=50,982,912 bytes, S=469, D=1, K=12.096041, points=54.132162.


## Official board results — raw feed observed 2026-10-31 01:25:23 UTC

Watcher healthy at `09ee42d8656b9b599401140eb38d5d76b07a7566`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-9d3a20bab5bd`, commit `09ee42d8656b9b599401140eb38d5d76b07a7566`; T=0.137588 s, M=51,347,456 bytes, S=469, D=1, K=12.184971, points=54.291224.


## Official board results — raw feed observed 2026-10-31 01:31:36 UTC

Watcher healthy at `ed14252dd1ed2a882887dffd6bb61950f03a1c85`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-b7259ab42416`, commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.136925 s, M=50,679,808 bytes, S=469, D=1, K=12.246449, points=54.400509.
- **LATEST:** `run-30c1524d873a`, commit `ed14252dd1ed2a882887dffd6bb61950f03a1c85`; T=0.138503 s, M=51,355,648 bytes, S=469, D=1, K=12.144267, points=54.218566.


## Wide unknown-region candidate not promoted

`sd-tc/main` commit `ac891520a08ace03690b070c17184af10c27aaab` adds a sentinel for `region_id=4,294,967,303`; CI [41155360298](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41155360298) passed the new fixture and official outputs/Docker. The frozen Track C spec caps region IDs at 9,999,999, so the new case is outside the scoring input contract. Its paired developer-runner full-scale comparison showed no gain (baseline/current median T≈0.21/0.22 s, RSS≈24,296/24,300 KiB). The >4,294,967,295 fixture remains optional robustness coverage, not a scoring qualification; this newer candidate is assessed on valid IDs below, including unknown values above 999,999.


## Official board results — raw feed observed 2026-10-31 01:36:50 UTC

Watcher healthy at `03742f51c5f91e7313584860fb6de63ad83fbae4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-2e4a2fbbc969`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.136063 s, M=50,782,208 bytes, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-2e4a2fbbc969`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.136063 s, M=50,782,208 bytes, S=469, D=1, K=12.280222, points=54.460311.


## Official board latest snapshot — raw feed observed 2026-10-31 01:42:00 UTC

Watcher healthy at `3077ed42f746f6ed84d122899e611b5af3dac0e4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-2e4a2fbbc969`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.136063 s, M=50,782,208 bytes, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-5c8e941c0c81`, commit `3077ed42f746f6ed84d122899e611b5af3dac0e4`; T=0.138843 s, M=50,831,360 bytes, S=469, D=1, K=12.154307, points=54.236511.


## Developer-main performance challenger — staged for official K

- Current `sd-tc/main` commit `400aa2dffa5d684e398043e2a13dd63463ceec3e`, source blob `da289c75f4d3894a3e432ad04a10d74066399c15`; only `join.cpp` imported, retaining the registered C++/zero-dependency manifest and Dockerfile. This includes bounded region lookups, batched parsing, reclamation of consumed input pages, and streamlined digit classification.
- CI [41155520691](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41155520691) passed official tiny/sample/full hashes, differential cases and pinned offline Docker. Full seed-1 comparison against the official BEST source also matched byte-for-byte locally (3,320,000 records; output SHA-256 `d8088b1cd42ba1338b1345b107b55db7b96ef1f5066f3ff64fd26a8912a0f536`). A valid-range edge fixture with unknown IDs 1,000,000 and 9,999,999 matched both the previous official source and Python reference (SHA-256 `c3f7c3ee178576d101aa00c561cb1696621aebedda1a0081473ae9ce7c3c41e4`).
- Seven interleaved full-seed-1 runs, same local compiler and three pinned CPUs: T median 0.408639 s (official BEST source) vs 0.264697 s (candidate, 35.2% faster); peak process RSS 247,112 vs 20,516 KiB. These are local measurements, not board axes.
- Source size estimate S≈563 (official S=469 plus 94 nonblank C++ lines); D=1. Applying local T/RSS ratios directly gives a rough K≈24.4, but board cgroup M may not scale with process RSS. With no M benefit, the same T/S estimate is K≈14.85. Both are estimates versus official BEST K=12.280222; the official run decides.

## Official K decision: developer-main challenger rolled back — 2026-10-31

The candidate passed all official board gates, but its measured scoring objective regressed. Board run `run-3f1acd6c12ff` on commit `d8e6e1c755acab6ab8ef167efed1b64d44f96c54` measured T=0.243185 s, M=17,563,648 bytes, S=572, D=1, K=11.025384, points=52.119687. Track C BEST remains `run-2e4a2fbbc969` at K=12.280222 (T=0.136063 s, M=50,782,208 bytes, S=469, D=1; commit `03742f51c5f91e7313584860fb6de63ad83fbae4`). Candidate correctness included the full valid region-ID range through 9,999,999 and unknown IDs above the lookup-table maximum of 999,999; an additional >4,294,967,295 robustness case is optional and is not a qualification requirement. Despite its lower measured memory and local runtime, official T and S caused lower K, so this integration restores the known-good source.

## Official board results — raw feed observed 2026-10-31 01:50:28 UTC

Watcher healthy at `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`, queue idle. All five gates passed for all four tracks; failures were null.

- **BEST:** `run-2e4a2fbbc969`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.136063 s, M=50,782,208 bytes, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-3f1acd6c12ff`, commit `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`; T=0.243185 s, M=17,563,648 bytes, S=572, D=1, K=11.025384, points=52.119687.

## Official rollback snapshot — raw feed 2026-10-31 01:55 UTC

`run-4b4cc28df120` scored commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; all five gates passed, failure null. This commit restores the exact C source blob measured as BEST. The restored source compiled with official static GCC flags and passed the organizer Track C suite (14 tests). **LATEST:** T=0.138231 s, M=52,301,824 bytes, S=469, D=1, K=12.111905, points=54.160623. **BEST:** `run-2e4a2fbbc969`, K=12.280222, points=54.460311.

## Official board snapshot — raw feed 2026-10-31 02:00:12 UTC

Watcher healthy at `6bf7383dc5439ccd0768435c1932c243e16c0584`, queue idle. All five gates passed, failure null. **BEST:** `run-2e4a2fbbc969`, K=12.280222, points=54.460311. **LATEST:** `run-7aaf768250b5`, T=0.138146 s, M=50,823,168 bytes, S=469, D=1, K=12.185323, points=54.291852.


## Official board results — raw feed observed 2026-10-31 03:05:10 UTC

The watcher was healthy at commit `b453c295cdbca2e3c740d71d6c35e57b8dec3662`. Run `run-6c39970c0495` on this commit passed build, check, correctness, timeout and sandbox gates. LATEST: T=0.138119 s, M=52,023,296 bytes, S=469, D=1, K=12.129762, points=54.192613. BEST remains `run-2e4a2fbbc969`: T=0.136063 s, M=50,782,208 bytes, S=469, D=1, K=12.280222, points=54.460311. This run did not replace BEST; retain the current source and track rollback history.


## Board baseline before multi-track trial — raw S3 feed 2026-10-31 03:49:18 UTC

- **BEST:** `run-2e4a2fbbc969`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-5a8a10bf4170`, official HEAD `a30276e460e00aa279aa41cca913a10a90a1a6a8`; T=0.138776 s, M=51,122,176 B, S=469, D=1, K=12.143378, points=54.216975. All five gates passed.

## C candidate board trial — rejected and rolled back

- Candidate source blob `ff0988db10568f3453c6f1f51564353c7a6130fc` scored as `run-fc7105cf4e5c` on commit `f91d9c075066881eb480cd7d27a9f33bfdc43350`. All five gates passed, but T=0.243243 s, M=17,969,152 B, S=578, D=1, K=10.956696, points=51.983981.
- Versus prior BEST `run-2e4a2fbbc969` (T=0.136063 s, M=50,782,208 B, S=469, K=12.280222), K fell 10.78%; lower memory did not offset 78.8% slower T and the larger S. Reverted to source blob `bdf2a15bc53d541b550536d292e43fc729575dbf` and the prior Dockerfile. The candidate remains recoverable in commit `f91d9c0`.


## Official baseline before Track B trial — raw feed 2026-10-31 04:14 UTC

On official HEAD `ec1140f4d0bd607a02b9fae4be61ce5fe3bae986`, LATEST `run-7079d672ee40` passed all five gates: T=0.139381 s, M=51,015,680 B, S=469, D=1, K=12.122049, points=54.178801. BEST remains `run-2e4a2fbbc969` (K=12.280222, points=54.460311). The baseline includes the rollback from the regressed C trial.


## Official board results after Track B trial — raw feed 2026-10-31 04:17:53 UTC

HighVelocity watcher healthy at `a2f99921eaf302381af4fa63e6b131588c3fb572`; `run-c904826315fc` passed all five gates. **LATEST:** T=0.145825 s, M=51,183,616 B, S=469, D=1, K=11.843399, points=53.673818. **BEST:** `run-2e4a2fbbc969`, K=12.280222, points=54.460311.


## Official board snapshot — 2026-10-31 04:21:29 UTC

HighVelocity (`highvelocity-7f330e`) watcher was healthy at official HEAD `a62ff8d662a8f342256a53b20e05a3e2a9af6231`; queue clear. All five gates passed.

- **BEST:** `run-2e4a2fbbc969`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-0c1c732b5642`; T=0.140275 s, M=50,884,608 B, S=469, D=1, K=12.089578, points=54.120556.


## Official board snapshot — 2026-10-31 04:25:59 UTC

- **BEST:** `run-2e4a2fbbc969`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-566915843b43` on `6ce631e9aed748609f3fbd289ec599cb4abf152d`; all five gates passed. T=0.138864 s, M=52,072,448 B, S=469, D=1, K=12.094895, points=54.130106.


## Official board snapshot — 2026-10-31 04:30:35 UTC

- **BEST:** `run-2e4a2fbbc969`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-0b56bf00d605` on `952084e36d4a8309c21c175f7208a40fe40c2702`; T=0.138386 s, M=50,749,440 B, S=469, D=1, K=12.178288, points=54.279311. All five gates passed.


## Official board snapshot — 2026-10-31 06:18:39 UTC

- **BEST:** `run-2e4a2fbbc969`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-afb1a3ddd3c5` on `bd1e696b8a738a9f6d52c2faa16d9a6244c64d5e`; all five gates passed. T=0.143447 s, M=50,851,840 B, S=469, D=1, K=11.956704, points=53.880574.


## Official board snapshot — 2026-10-31 06:23:31 UTC

- **BEST:** `run-2e4a2fbbc969`; T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-60614c3c28a0` on `8e70985f8a07fc6b5adaa9435c4d6b83638a2665`; all five gates passed. T=0.140332 s, M=51,019,776 B, S=469, D=1, K=12.080711, points=54.104624.

## Official board receipt — 2026-10-31 06:59:47 UTC

- Run `run-b0f2b558fb83` scored commit `f3bd76617870c71c81594817b54ad366113718bc`; all five gates passed. LATEST: T=0.139924 s, M=51,216,384 B, S=469, D=1, K=12.089008, points=54.119533. BEST remains `run-2e4a2fbbc969`: K=12.280222. This receipt is 1.557% below BEST; no Track C source change was included.

## Official board snapshot — 2026-10-31 07:06:34 UTC

- `run-adc61c5cc48c` scored `281c60f59cbe6c6a8c51f77aba7daad102151abd`; all five gates passed. LATEST: T=0.144858 s, M=51,318,784 B, S=469, D=1, K=11.876597. BEST remains `run-2e4a2fbbc969` (K=12.280222); no C source change was present in that snapshot.

## Official board snapshot — 2026-10-31 07:12:34 UTC

- `run-d41639cdb467` scored `aa84dc52fefa309db4dbc5c2b9aefc07863ea13a`; all five gates passed. LATEST: T=0.141537 s, M=50,606,080 B, S=469, D=1, K=12.048778. BEST remains `run-2e4a2fbbc969` (K=12.280222); no C source change was present in this snapshot.

## Official board snapshot — 2026-10-31 07:17:07 UTC

- `run-fb43b5231132` scored exact HEAD `15cc7c6f38a26d0f3515727d6d217ba4d95094b9`; all five gates passed. LATEST: T=0.137623 s, M=51,052,544 B, S=469, D=1, K=12.197465, points=54.313478. BEST remains `run-2e4a2fbbc969` (K=12.280222).


## Official board snapshot — 2026-10-31 12:11:52 UTC

- **BEST:** `run-2e4a2fbbc969`, T=0.136063 s, M=50,782,208 B, S=469, D=1, K=12.280222, points=54.460311.
- **LATEST:** `run-14944aa00726` on `2b5afc9408dcd202ca3f113e100d02fc673d04ee`; all five gates passed. T=0.139937 s, M=51,236,864 B, S=469, D=1, K=12.087480, points=54.116788.
- Candidate source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` is from `sd-tc/main` HEAD `eb1ab4a2979106afd223d8c638fda89a66adcaed`; exact-source qualification CI `41197476950` passed. Paired runner median changed 148.067 to 147.923 ms and peak RSS 18,980 to 16,920 KiB; these are developer-runner measurements, not board T/M/K. Candidate board result is pending; parent commit retains the known-good source for rollback.


## Official candidate result — 2026-10-31 12:15:45 UTC

- Board run `run-26bebca7d52d` scored `187269afc6efbeee7ac01b4f623f7c7f049ea44b`; all five gates passed. **LATEST and new BEST:** T=0.128998 s, M=10,719,232 B, S=518, D=1, K=16.959803, points=61.471040. Prior BEST `run-2e4a2fbbc969` had K=12.280222. K improved 38.11%, with 5.2% lower T and 78.9% lower M despite the larger source axis; promote source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`. Rollback is parent commit `2b5afc9`, source blob `bdf2a15bc53d541b550536d292e43fc729575dbf`.


## Official latest — 2026-10-31 12:21:24 UTC

- **BEST:** `run-26bebca7d52d`, K=16.959803. **LATEST:** `run-c9eb30305694` on `ca8f1811fcefc6fdb6cc5678754f7387791f5f31`; all five gates passed. T=0.130200 s, M=10,522,624 B, S=518, D=1, K=16.943952, points=61.450736. This 0.09% difference is within run variation; retain the same source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`.


## Official latest — 2026-10-31 12:26:53 UTC

- BEST remains `run-26bebca7d52d`, K=16.959803. LATEST `run-ed1504154f56` on `f3b24e34ddb937f3bca3317cfd5d79bf021509fa` passed all gates: T=0.128603 s, M=10,866,688 B, S=518, D=1, K=16.939478, points=61.445001. The 0.12% difference is within run variation; keep source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`.


## Staged exact-name prefetch trial — pending official board

- Candidate source blob `dad49158dad5f90d32ab5eb307eb9a62e138723e` from `sd-tc/main` HEAD `b29de1927e809a2d0bf89ea0d6e236dcef3d2e85`. It prefetches the exact-name shard slot while the CSV parser processes the intervening note/amount fields. Exact-source CI `41201156576` and paired comparison `41201287339` passed.
- Across 12 paired full-seed runner trials, baseline `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` median was 146.629 ms / 16,918 KiB; candidate was 140.258 ms / 16,916 KiB. This is developer-runner evidence, not scoring-box T/M/K. Candidate adds four source lines; board result is pending. Parent `476d415` preserves C BEST source `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` for rollback.


## Exact-name prefetch official trial — rejected, 2026-10-31

- Run `run-cfb141b4fcbd` on `f477933130ce23aa311f60d3486480ab5de6fff8` passed all five gates. Prefetch candidate LATEST: T=0.131419 s, M=10,739,712 B, S=524, D=1, K=16.767456, points=61.223359. BEST remains `run-26bebca7d52d`, K=16.959803. The candidate was 1.13% below BEST, slower and six source lines larger; restore the prior BEST blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` from parent `476d415`. The measured runner improvement did not transfer to the scoring box.

## Official latest — 2026-10-31 12:33:30 UTC

- BEST remains `run-26bebca7d52d`, K=16.959803. LATEST `run-cfb141b4fcbd` passed all gates: T=0.131419 s, M=10,739,712 B, S=524, D=1, K=16.767456. Known-good C source is restored pending rescore.

## Developer-main per-thread cache trial — rejected before submission

- Track C `main` HEAD `a97a4ac5a83c1a78bd2630015debf3e934ea91cf` added a per-thread exact-name cache; its exact-source CI `41201618354` passed correctness/container checks, but the 12-pair full-seed comparison regressed from 139.972 ms / 16,850 KiB to 153.091 ms / 19,544 KiB. Reject without an official board trial; retain the `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` C source.


## Official latest — 2026-10-31 12:40:42 UTC

- **BEST:** `run-26bebca7d52d`, K=16.959803. **LATEST:** `run-750e8d23bd64` on `0923ede528139a79896a6bfe1bb67934f74c5951`, all five gates passed: T=0.129279 s, M=10,825,728 B, S=518, D=1, K=16.907897, points=61.404480. Same promoted source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`; 0.31% below BEST.

## Official same-source rerun — 2026-10-31 13:17 UTC

- Run `run-fdb7d388d133` on `b0e30144ba58e2c3b3c86c8b1fd26dffa1e655b5` passed all five gates: T=0.148486 s, M=10,461,184 B, S=518, D=1, K=15.884959. BEST remains `run-26bebca7d52d` (K=16.959803). Source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` is unchanged; this lower run is ordinary scoring variation, not a new candidate.


## Official latest before guarded-BOM CRC trial — 2026-10-31 13:23:53 UTC

- BEST remains `run-26bebca7d52d`, K=16.959803. LATEST `run-9da1c936d35e` on `f1bcd2033e061028929c445c964768331d1a6f5e` passed all five gates: T=0.137903 s, M=10,522,624 B, S=518, D=1, K=16.463924, points=60.826667. Existing source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` was unchanged in that run.

## Guarded-BOM CRC candidate — rejected by official board, 2026-10-31

- Candidate source blob `efcc37be6d82c3e341eaa3d66f2e7af82338ee07` from `sd-tc/main` HEAD `9a3f26ee245a35ad97d4cad75297e0148f6d4738`. The source replaces quoted-name hashing with CRC32C over the unique raw CSV encoding and checks for a BOM before invoking the full BOM handler. It does not change region-ID parsing/mapping; IDs through 9,999,999 remain supported and unknown IDs still map to the unmatched group.
- Independent source-identical CI `41206065495` passed full seed-1 hash, holdout seeds, hostile cases, offline Docker and sandbox. Across 12 paired runner trials, T median was 136.822→134.671 ms, RSS 16,920→16,852 KiB, physical source lines 460→454; estimated complete-K proxy +1.08% (runner evidence only). The candidate Dockerfile uses the same pinned allowlisted images with explicit `-march=x86-64-v3` for CRC intrinsics. Official run `run-0bffab996db6` on `af33cf8053e100e92405aabcfa50d0278203daa1` passed all five gates: T=0.131801 s, M=10,661,888 B, S=516, D=1, K=16.806251, points=61.273542. BEST remains `run-26bebca7d52d` (K=16.959803). Candidate was 0.91% lower in K and 2.18% slower despite 0.53% less memory and two fewer source lines; the +1.08% runner K proxy did not transfer. Restored the exact BEST source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` and original Dockerfile from parent `f1bcd20`; `efcc37be6d82c3e341eaa3d66f2e7af82338ee07` remains recoverable in history.


## Official same-source result — 2026-10-31 14:22 UTC

- **BEST and LATEST:** `run-cc78d8d94587` on `e5e94a469faec38eaaf180210e468ac3060b3023`, all five gates passed: T=0.126735 s, M=10,743,808 B, S=518, D=1, K=17.102716, points=61.653254. This is a new BEST on unchanged source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`, up 0.84% from `run-26bebca7d52d`.

## Guarded SWAR parsing — rejected by official board, 2026-10-31

- Candidate source blob `b5e2c905648d759a15c34ea2e5bd6eed130e9386` from `sd-tc/main` (commit `83f7b034d453af66be0660369a192d830d43eb3f`) passed exact-source CI `41210875048`: full seed-1 hash, holdout seeds, collision/overflow/long-integer cases, offline Docker, sandbox, and an eight-digit-ID fixture. Its paired runner medians were 79.544→77.514 ms and RSS 17,094→17,172 KiB; those runner measurements did not predict the scoring-box result.
- Official LATEST `run-58ac60385064` on submission `1657706f033d676bb97f0df87e3386978b694387` passed check/build/correctness/timeout/sandbox, with T=0.106212 s, M=21,200,896 B, S=518, D=1, K=16.307500, points=60.619369. Compared with BEST `run-cc78d8d94587` (K=17.102716, T=0.126735 s, M=10,743,808 B), K fell 4.65% and memory nearly doubled despite lower T.
- Reject this candidate and restore the BEST source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` and its prior Dockerfile (blob `63226602c9a43a0a3584038708a213a7132834b6`). The rejected trial remains recoverable from parent commit `1657706f033d676bb97f0df87e3386978b694387`.

## Official latest — 2026-10-31 15:21 UTC

- LATEST `run-39536802a1c6` on `480a8e3def26af26e10298d6b043bf2195c82ec3` passed all five gates: T=0.133971 s, M=10,772,480 B, S=518, D=1, K=16.625567, points=61.038824. BEST remains `run-cc78d8d94587`, K=17.102716. This run used the restored unchanged source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`; the lower same-source score is a repeat, not a code change.

## Official latest — 2026-10-31 16:13 UTC

- LATEST `run-3e021bc33700` on `8298e2cbe0d21ffd4688bb23b625f988fdd4128d` passed all five gates: T=0.136147 s, M=10,846,208 B, S=518, D=1, K=16.469689, points=60.834270. BEST remains `run-cc78d8d94587`, K=17.102716. C source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` was unchanged.


## Official latest — 2026-10-31 16:19 UTC

- LATEST `run-2984955b27ba` on submission `d4b9c4d51f4d0c3fc2d58a1fc9bf6c66ef642ed9` passed all five board gates: T=0.129916 s, M=10,604,544 B, S=518, D=1, K=16.936174, points=61.440765. BEST remains `run-cc78d8d94587`, K=17.102716; restored C source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33` unchanged. Qualification includes valid region IDs through 9,999,999; larger IDs are optional robustness cases.


## Official latest and candidate trial — 2026-10-31 16:27 UTC

- Current rollback LATEST `run-658fa792dd37` on official commit `70d512481b36d111e017909f4b76e257f69db9ea` passed all five gates: T=0.126929 s, M=11,141,120 B, S=518, D=1, K=16.965975, points=61.478941. BEST remains `run-cc78d8d94587`, K=17.102716; rollback source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`.
- This release stages source blob `f2cac0cd833c1b746d28c1ff143be66c013da0d9` from open `sd-tc` PR #4 (source commit `734dfc25e57df255fb0c7e4109df486103347693`) as a controlled official trial. Developer qualification reports exact full/sample/tiny parity, adversarial fixtures including a 2 MB name, and ASan/UBSan plus TSan on sample seed 2. Paired local full Docker medians: 245.7→227.6 ms; cgroup peak 20.548→19.739 MB (12 runs, two-core quota). These are local results, not official scoring evidence. Exact commit has no GitHub Actions run; developer reports pinned GCC Docker build was blocked by local VFS capacity, while static offline runtime passed. Official Docker and full-board correctness remain pending.
- `regions.csv` generated lookup IDs stay within 1–999,999; record IDs may reach 9,999,999. The candidate reads record IDs as `uint64_t`, maps absent IDs above the dense lookup range to the unmatched group, and leaves optional IDs above the frozen limit as robustness-only.

## Official promotion — inline exact-name dictionary, 2026-10-31

- Official trial `run-f7675699a941` on commit `0ef3758e08e015c6f1ba97b9d36966ec151efc40` passed all five gates: T=0.073774 s, M=20,750,336 B, S=459, D=1, K=20.010866, points=65.063294. This is new BEST and LATEST, +17.00% K versus prior BEST `run-cc78d8d94587` (K=17.102716); runtime fell 41.8%, memory rose 93.1%, and source S fell from 518 to 459. No third-party runtime dependencies.
- Promoted source blob `f2cac0cd833c1b746d28c1ff143be66c013da0d9` from `sd-tc` PR #4 was merged to `sd-tc/main` at `bed77c986abef152713ead8405cba08a5c85c19f`. Parent official commit `70d512481b36d111e017909f4b76e257f69db9ea` retains the known-good rollback source blob `3cecd2945c284b4ae1684f9f1779bb0607cc1e33`.
- Exact-source CI on merged main, run `41220403158`, passed tiny/sample/full differential exactness and completed paired runtime/RSS tests; it then failed in the unscored phase profiler because `tests/profile_track_c.py` asserted an obsolete source statement (`std::vector<Group> groups = merge_workers(...)`). The pinned Docker and sandbox steps were skipped after that assertion. The official board independently built this exact candidate and passed build, full correctness, timeout and sandbox gates. The runner comparison against the developer's newer `f875b5d3` source was slower/higher-RSS (104.002→109.445 ms; 17,106→30,746 KiB); board scoring against the installed official champion improved K as recorded above. Review/update the profiler before claiming all developer CI green.


## Low-memory control-byte table — official trial pending, 2026-10-31

- Candidate from open `sd-tc` PR #5, source commit `d1189c62ac6d6e56ba034e57919f0de3dc0f5128`, blob `7def6ac05e18fcf871310f37abade9ca1a904760`. It changes the exact-name table to 131,072 control-byte-probed slots with inline short keys and a synchronized overflow path.
- Developer report: full seed-1, sample seeds 1/2, tiny seeds 1/2/3 and adversarial cases pass; 160,000-record overflow/repeated-name reference fixture passed ASan/UBSan and TSan. Paired static-Docker full runs (12, two-core quota) versus PR #4 inline source: T=229.093→243.072 ms and peak cgroup M=19.739→11.434 MB. The K proxy is +5.7% after source-size cost; this is local evidence only. No Actions run exists for the exact commit, and the pinned GCC build was blocked by the developer's VFS limit; official build/correctness/scoring are pending.
- Current official BEST before this trial is `run-f7675699a941`, K=20.010866. PR #4 remains the rollback source in parent `92c095f030bd9519de41ab7201a944cc9d94cbd6` (blob `f2cac0cd833c1b746d28c1ff143be66c013da0d9`). Merge PR #5 only if the live-board run passes all gates and beats K=20.010866.


## PR #5 qualification resolved — 2026-10-31 16:45 UTC

- After the official trial completed with all gates passing, PR #5 was merged to `sd-tc/main` as `0c026e2b3d0003f85f3ce88de1fc94522128d0b6`; its source blob is `7def6ac05e18fcf871310f37abade9ca1a904760`. PR #4's inline-name implementation remains in official history and is the rollback candidate.
- **BEST / LATEST:** official run `run-dd8b39dbecd2` on commit `242c9bf8b5169359fbe30b30245cf799f1662304` passed check, build, correctness, timeout, and sandbox gates: T=0.085478 s, M=12,455,936 B, S=537, D=1, K=20.109251, points=65.169794.
- Before/after against the immediately preceding official C BEST, `run-8a3385ae3968` on `92c095f030bd9519de41ab7201a944cc9d94cbd6`: T 0.073584→0.085478 s (+16.2%), M 20,631,552→12,455,936 B (-39.6%), S 459→537 (+78), K 20.059703→20.109251 (+0.25%). This narrowly improves K while materially reducing measured memory; retain the previous source for rollback.
- Developer differential, adversarial, sanitizer, and offline static-Docker evidence is recorded above. No GitHub Actions run exists for the exact PR #5 head; its pinned GCC Docker workflow was blocked by the developer's local VFS storage limit. The official board independently built and passed exact candidate correctness and sandbox gates.
- Prior C BEST before run `run-8a3385ae3968` was `run-f7675699a941` (K=20.010866). The feed's earlier tentative threshold is superseded by the measured 92c result.


## Repeated official run after PR #5 promotion — 2026-10-31 16:49 UTC

All five gates passed on commit `6a01ff11b17d179835197e73cbab6518a6651b79` with merged PR #5's same control-byte source.

- **BEST / LATEST:** `run-4338f0eff51f`: T=0.084500 s, M=12,615,680 B, S=537, D=1, K=20.173806, points=65.239392.
- Against the prior same-source run `run-dd8b39dbecd2` (T=0.085478 s, M=12,455,936 B, K=20.109251), this measured K is 0.32% higher. No code changed between runs; retain both measurements as board variance, with `run-4338f0eff51f` the current BEST and LATEST.


## Full-team board run — 2026-10-31 16:54 UTC

All five gates passed on official commit `77a70106fecd5098a0a152a47f8e7383a3c1e9c5` with the promoted PR #5 source. **BEST / LATEST:** `run-13bca81389a0`, T=0.084854 s, M=12,288,000 B, S=537, D=1, K=20.237923, points=65.308297. Source was unchanged from `run-4338f0eff51f` (K=20.173806); this repeated result is +0.32% K and becomes BEST and LATEST.


## Latest board result — 2026-10-31 17:00 UTC

All five gates passed on commit `74a4fb7456ce5fb8b10ef5b0eeef2d58289fdc59` with the unchanged promoted PR #5 source. **LATEST:** `run-e18434258740`, T=0.086174 s, M=12,623,872 B, S=537, D=1, K=19.974306, points=65.023585. Current BEST remains `run-13bca81389a0`, K=20.237923; the latest same-source K is 1.30% lower, consistent with the observed run-to-run variability.


## Full-team board run — 2026-10-31 17:05 UTC

All five gates passed on commit `23be16823a7232064b3090b805ff80b6c086cfa9` with the PR #5 source. **BEST / LATEST:** `run-955f007ac420`, T=0.084295 s, M=12,238,848 B, S=537, D=1, K=20.321199, points=65.397466. This improves the prior same-source BEST `run-13bca81389a0` (K=20.237923) by 0.41%; the source is unchanged, so preserve the observed variance in comparisons.


## Full-team board result — 2026-10-31 17:10 UTC

All five gates passed on official commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818` with merged PR #5 source. **LATEST:** `run-33c779216ad5`, T=0.083881 s, M=12,558,336 B, S=537, D=1, K=20.266564, points=65.339006. BEST remains `run-955f007ac420`, K=20.321199.


## Full-team board result — 2026-10-31 17:19 UTC

All five gates passed on official commit `c4cb49fedd910dd65dc0719c113b06fa2e9c2476` with the unchanged merged PR #5 source. **LATEST:** `run-f3f88a1bbcc0`, T=0.086720 s, M=12,292,096 B, S=537, D=1, K=20.017669, points=65.070676. BEST remains `run-955f007ac420`, K=20.321199.


## Official baseline on rollback HEAD — 2026-10-31 17:30 UTC

All five gates passed on `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122` using the promoted PR #5 source. **LATEST:** `run-712d84a60eed`, T=0.084741 s, M=12,328,960 B, S=537, D=1, K=20.237938, points=65.308313. BEST remains `run-955f007ac420`, K=20.321199.

## PR #7 certified-split + CRC/SWAR candidate staged

- PR #7 head `dcb50168fcfb8b8b75b6eebc8c03976c589d056e`, source blob `dc7d92e9f2ab8e30bbd7b90a69360e22648c939a`; it combines certified record splitting, wide CRC32C tail hashing and guarded SWAR integer decoding. The PR remains open and mergeable; its rollback source is the current official C candidate from PR #5.
- CI [41227918470](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41227918470) passed official tiny/sample/full hashes, seed 2/3, adversarial/overflow/long records, ASan/UBSan, TSan, pinned offline GCC Docker and sandbox.
- Paired developer-runner median was 97.164→85.725 ms and sampled RSS 22,498→22,250 KiB across 12 trials; D remains 1. This does not establish official six-core T/M/S/K. Official BEST is K=20.321199; trial result pending.


## Official rollback after failed Docker build — run-7c225263b59a (2026-10-31 18:17 UTC)

- Candidate from open `sd-tc` PR #7 failed the official build stage: check=true, build=false; public feed reports Docker build exit 1. No T/M/S/D/K was produced. The feed does not expose a build-log tail, so no cause is inferred.
- Restored the previously qualified Track C source from parent commit `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122`; its source matches the candidate that produced BEST `run-955f007ac420`.
- **BEST:** `run-955f007ac420`, T=0.084295 s, M=12,238,848 B, S=537, D=1, K=20.321199, points=65.397466.
- **LATEST:** `run-7c225263b59a` (failed build; no score). PR #7 remains open and unmerged pending developer correction. Candidate source and failed run remain in official Git history for review/rollback.


## Official baseline and PR #8 trial staged — 2026-10-31

- On the restored known-good source, all five gates passed in **LATEST** `run-2834c7216378`: T=0.084820 s, M=12,374,016 B, S=537, D=1, K=20.213758, points=65.282353. **BEST** remains `run-955f007ac420`, K=20.321199.
- Staged the candidate from open `sd-tc` PR #8, head `b7bb0d5c32b2aa06cd1d046d4dabf31d65cd0389`, source blob `11bfcc0ba501d22454a8f21a06e23ad020183efd`. CI [41228157740](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41228157740) passed full/sample/tiny references, adversarial overflow/collision/long-record cases, ASan/UBSan, TSan, pinned offline Docker, and sandbox checks.
- Developer paired runner medians: 148.377→129.688 ms, RSS 22,618→20,374 KiB across 12 trials. Reported complete-K proxy +9.2% on CI and +6.3% in local static Docker versus its official-source baseline; these are not official scores. Candidate source has 545 physical lines versus the current 537.
- **Candidate LATEST official result: pending.** Parent commit `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21` retains the known-good current source for rollback. PR #8 is not merged pending official gates and K.


## Official PR #8 build result — run-adcadeec9db2 (2026-10-31 18:31 UTC)

- Trial from open PR #8 failed the official build stage: check=true, build=false; public feed reports `docker build failed (exit 1)`. No correctness/sandbox result or T/M/S/D/K was produced. The public feed provides no build-log tail; no cause is inferred.
- Restored known-good source blob `7def6ac05e18fcf871310f37abade9ca1a904760` from parent `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`. **BEST:** `run-955f007ac420`, K=20.321199. **LATEST:** `run-adcadeec9db2`, failed build / unscored.
- PR #8 stays open and unmerged pending developer diagnosis. Candidate source remains available in official history at `5b1f942cac523c62dcda40eca63586732c6a7959`.


## Official rollback result — run-8f98e6ec4091 (2026-10-31 18:37 UTC)

After restoring known-good source blob `7def6ac05e18fcf871310f37abade9ca1a904760`, all five gates passed. **BEST/LATEST:** T=0.082831 s, M=12,500,992 B, S=537, D=1, K=20.413289, points=65.495649. This replaces the prior BEST `run-955f007ac420` (K=20.321199) on the same source. The failed PR #8 build remains LATEST only for its prior trial commit; it is not the current source result.


## Official latest — run-273326332bcf (2026-10-31 18:44 UTC)

All five gates passed on restored source blob `7def6ac05e18fcf871310f37abade9ca1a904760`. **LATEST:** T=0.087211 s, M=12,734,464 B, S=537, D=1, K=19.820590, points=64.855828. **BEST** remains `run-8f98e6ec4091` (K=20.413289).

## Track C main candidate staged — official trial pending

- Current developer main HEAD `0a65827a4d09bbb397cb3dea20990c214346d863` restores the SSE2 quote-scanning source, blob `4ca129b0ca9596554d052aadb9d5e751496cc754`. That exact source was qualified by CI [41229750254](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41229750254): full seed-1 hash, holdout seeds, quote-boundary, offline Docker and sandbox checks passed.
- Developer paired runner medians were 103.962→100.798 ms (RSS 17,146→17,158 KiB, proxy +1.18%) and independent replication 140.930→132.367 ms (RSS 17,070→17,112 KiB, proxy +2.77%). The proxy compares against developer source `f875b5d`; it is not an official board measurement. Source and D differences are recorded by the developer; official T/M/S/D/K remain pending.
- Candidate is imported from developer main, not an open PR. Rollback is the known-good source in parent `f0e8236ee3641950287d6e2dd25814fb4b6ef9bb`. The separate open PR #8 source failed official Docker build (`run-adcadeec9db2`) and remains unmerged.


## Official first build attempt for current-main SSE2 source — run-ab5d43ee092f (2026-10-31 18:50 UTC)

- Check passed, Docker build failed (exit 1; public feed has no tail). No correctness/sandbox result or T/M/S/D/K was produced. The source-identical developer CI passed, but build configs differ: developer `track-c/Dockerfile` uses `-march=x86-64-v3`, while official Dockerfile omitted it. The current source uses SSE4.2 CRC intrinsics; align the official compiler target with the verified developer build for a controlled retest. No private board log was accessed and no hidden failure detail is claimed.
- Keep known-good source blob `7def6ac05e18fcf871310f37abade9ca1a904760` from parent `f0e8236ee3641950287d6e2dd25814fb4b6ef9bb` as rollback. Candidate score remains pending after build configuration repair.


## Official SSE2 candidate retest — run-814a3a4d2917 (2026-10-31 18:56 UTC)

- After matching the developer's `-march=x86-64-v3` compile target, all five gates passed, but the candidate source blob `4ca129b0ca9596554d052aadb9d5e751496cc754` scored T=0.106733 s, M=21,266,432 B, S=536, D=1, K=16.174523, points=60.441574. This is far below the known-good BEST `run-8f98e6ec4091`, K=20.413289.
- Reject for promotion. Restored champion source blob `7def6ac05e18fcf871310f37abade9ca1a904760` and original official Dockerfile from parent `f0e8236ee3641950287d6e2dd25814fb4b6ef9bb`. Candidate remains in commit `6b8e8c7ce01eb50f1063be84119cc111c03ff5cb`; it came from developer main, so no PR is eligible to merge.


## Official rollback latest — run-0ab335e21341 (2026-10-31 19:02 UTC)

All five gates passed on restored champion source `7def6ac05e18fcf871310f37abade9ca1a904760` with the original official Dockerfile. **LATEST:** T=0.084718 s, M=12,656,640 B, S=537, D=1, K=20.134776, points=65.197340. **BEST** remains `run-8f98e6ec4091` (K=20.413289).


## Official latest — run-e081c61ac0cb (2026-10-31 19:08 UTC)

All five gates passed. **LATEST:** T=0.083898 s, M=12,500,992 B, S=537, D=1, K=20.283067, points=65.356682. **BEST** remains `run-8f98e6ec4091` (K=20.413289).


## Official latest — run-1c44e3197d43 (2026-10-31 19:15 UTC)

All five gates passed. **LATEST:** T=0.083959 s, M=12,783,616 B, S=537, D=1, K=20.185242, points=65.251698. **BEST** remains `run-8f98e6ec4091` (K=20.413289).


## Official latest — run-039069482c2a (2026-10-31 19:24 UTC)

All five gates passed. **LATEST:** T=0.084327 s, M=12,537,856 B, S=537, D=1, K=20.219497, points=65.288518. **BEST** remains `run-8f98e6ec4091` (K=20.413289).


## Official latest — run-662f71c28451 (2026-10-31 19:29 UTC)

All five gates passed. **LATEST:** T=0.085472 s, M=12,312,576 B, S=537, D=1, K=20.156569, points=65.220831. **BEST** remains `run-8f98e6ec4091` (K=20.413289).


## Frontier PR #11 official trial queued

Testing exact PR branch revision `59e47be4236db4fc246673fec87e25bbd7231780` (source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`) with its matching PGO Dockerfile and generator context. CI `41231997313` passed pinned offline GCC 15, sandbox, ASan/UBSan, TSan, collision checks, and full seeds 11/29 (three repeats). Paired full-PGO median 135.220→134.717 ms and RSS 17,660→17,084 KiB; local static Docker M 9,668,608→8,855,552 B. These are developer measurements, not official scoring axes. **BEST remains `run-8f98e6ec4091` (K=20.413289)** pending board evaluation. Preserve current source and Dockerfile in parent `492f9dd3` for rollback; merge PR #11 only if promoted.


## Official PR #11 result — run-15adbc1f561c (2026-10-31 19:42 UTC)

All five gates passed on exact CI-tested source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`, with PR PGO Dockerfile and generator context. T=0.076727 s, M=14,487,552 B, S=552, D=1, K=20.508340, points=65.596525. This exceeds prior BEST `run-8f98e6ec4091` (K=20.413289); record this as **BEST** for the tested revision. PR #11 current head `23bf44f9` adds `#pragma GCC target("arch=x86-64-v3")`; test that exact head before merging because CI and this official run predate the pragma. The PR base has since diverged from main.

## Frontier PR #11 head trial

Now testing current open PR head source blob `78503e708dccdbf484bb5dc1223a02705cfabb81` with matching PGO Dockerfile/generator. Roll back to parent `8df4a7a5` context if it fails or loses K.

## Official board run — 2026-10-31 19:46 UTC

Run `run-9722acb5cb38` scored commit `2602c63339f532be813056b0c05bb573835f6766`; all five gates passed, failure null. **LATEST:** T=0.096269 s, M=13,807,616 bytes, S=553, D=1, K=18.480714. This exact PR #11 head added `#pragma GCC target("arch=x86-64-v3")` and regressed versus its previously tested predecessor. **BEST** remains `run-15adbc1f561c`, K=20.508340 (tested packed 48-byte source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`, Dockerfile, and generator context). Restore that tested revision; keep the PR-head regression informative and rejected.

## Official board result — commit 3384246, dispatch 2026-10-31 19:52 UTC

Run `run-27cd5c419972`; all five gates passed. T=0.095782 s, M=14,618,624 bytes, S=552, D=1, K=18.322316, points=63.149018. **BEST:** `run-15adbc1f561c`, K=20.508340. **LATEST:** `run-27cd5c419972`. The code is the tested PR #11 predecessor (packed 48-byte source; C PR #11 is merged to developer main with the regressing pragma excluded). Next frontier candidate: C PR #8, exact head `252788a42652b525330b690b5939c9c8a9d2f519`, CI `41228157740` passed correctness, sanitizers, pinned Docker, and sandbox. Its paired local complete-K proxy was +6.3% versus the official baseline; this is not an official score.

## Official board result — commit 13b8fec, dispatch 2026-10-31 19:57 UTC

Run `run-7911aaf80ec0`; all five gates passed. T=0.086669 s, M=14,110,720 bytes, S=545, D=1, K=19.435391, points=64.429664. **BEST:** `run-15adbc1f561c`, K=20.508340. **LATEST:** `run-7911aaf80ec0`. C PR #8's official trial did not beat BEST; leave it open and do not promote. Next is C PR #2 speculative split, exact head `ac03e464e73044bdd99034a9b4565de96ef8becb`, source blob `4237daa7464822fd4768fb5e93d40d1f2fe141ca`. Developer full/sample/tiny/adversarial outputs matched references; local full runs 230.1→214.6 ms and 436.3→408.4 CPU-ms; static Docker runtime passed, while local pinned build hit the VFS storage limit. No official score had previously been claimed.

## Official board result — commit 555cd61, dispatch 2026-10-31 20:03 UTC

Run `run-2de5259cd705`; all five gates passed. T=0.231307 s, M=18,325,504 bytes, S=515, D=1, K=11.387223, points=52.820891. **BEST:** `run-15adbc1f561c`, K=20.508340. **LATEST:** `run-2de5259cd705`; C PR #2's speculative split is rejected on official K, despite local correctness and runtime evidence. Restore the previously board-tested PR #11 predecessor context (join blob `59974fd...`, its Dockerfile and generator).


## Official board result — trial commit 9743d05 (2026-10-31 20:09:57 UTC)

Run `run-46bba325d2ca`; all five gates passed. T=0.075070 s, M=14,110,720 B, S=552, D=1, K=20.843017, points=65.948029. **BEST = LATEST:** K=20.843017, ahead of prior qualified BEST `run-15adbc1f561c` (K=20.508340). This was the restored, previously tested C champion source and runtime/size context; no open frontier PR supplied this winning source.


## Official board result — commit 3c9845a (2026-10-31 20:15:02 UTC)

Run `run-804f529ac682`; all five gates passed. T=0.074402 s, M=14,258,176 B, S=552, D=1, K=20.892890, points=65.999926. **BEST = LATEST:** K=20.892890, improving on same champion-source run `run-46bba325d2ca` (K=20.843017) and prior BEST `run-15adbc1f561c` (K=20.508340). Source blob remains `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`.


## Official board result — commit fa0f0b4 (2026-10-31 20:20:02 UTC)

Run `run-1eabfabdfaa6`; all five gates passed. T=0.074252 s, M=14,405,632 B, S=552, D=1, K=20.870991, points=65.977154. **LATEST**; **BEST** remains `run-804f529ac682` at K=20.892890.


## Official board result — commit c2397c9 (2026-10-31 20:26:59 UTC)

Run `run-f81420fd16be`; all five gates passed. T=0.075201 s, M=14,495,744 B, S=552, D=1, K=20.713033, points=65.812185. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890).


## Official board result — reserve-trial commit 74145b5 (2026-10-31 21:10:54 UTC)

Run `run-4af82d38aa0a`; all five gates passed on the unchanged C champion source. T=0.077486 s, M=14,053,376 B, S=552, D=1, K=20.532218, points=65.621793. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890).


## Official board result — champion-only commit ac7ea0e (2026-10-31 21:15:54 UTC)

Run `run-c797af1d84e8`; all five gates passed. T=0.077881 s, M=14,204,928 B, S=552, D=1, K=20.436196, points=65.520002. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890).


## Official board result — commit 260134e (2026-10-31 21:23:17 UTC)

Run `run-932de2fd192c`; all five gates passed. T=0.076685 s, M=14,290,944 B, S=552, D=1, K=20.570091, points=65.661811. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890). This scored the prior C source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`.

## Mainline AVX2 quote-scan candidate — awaiting official validation

Promoted developer main source blob `6b3f574b308b97bab15a23930ec9a09f6d18a666` after two independent full-PGO CI runs, [41243264138](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41243264138) and [41243555329](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41243555329). Both passed full seed-1 SHA-256, holdout full seeds 11/29, hostile parser cases, ASan/UBSan/TSan, pinned offline Docker, sandbox and independent references. The guarded AVX2/SSE2 quote scanner with scalar tail measured 109.171→104.134 ms (RSS 16,892→16,592 KiB) and 110.434→105.698 ms (RSS 17,020→16,572 KiB) on paired 12-trial developer runners; the estimated complete-K proxy was +2.15% in both trials. Source lines grew 469→488; formatter S and official cgroup M/K remain pending. Current official candidate is unchanged until board validation. Previous official C source remains in parent `260134e` for rollback.


## Official board result — commit 954e3c7 (2026-10-31 22:12:50 UTC)

Run `run-ac0bb7bc352e`; all five gates passed. T=0.074156 s, M=14,467,072 B, S=577, D=1, K=20.728546, points=65.828441. This did **not** beat BEST `run-804f529ac682` (K=20.892890); the AVX2 quote-scan trial's S rose from 552 to 577 and eroded the small runtime gain. **LATEST** is this measured trial. Restore the known-good C source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`; candidate commit `954e3c7` is retained as rollback/evidence history.


## Official board result — commit 62eaaeb (2026-10-31 23:10:08 UTC)

Run `run-2984194a5a86`; all five gates passed. T=0.081396 s, M=14,643,200 B, S=552, D=1, K=19.868949, points=64.908744. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890). This measured the restored known-good source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`; runtime variation worsened the repeated score, with no source change.


## Official board result — commit 97ebf28 (2026-10-31 23:15:08 UTC)

Run `run-33cbfdcb15ee`; all five gates passed. T=0.074595 s, M=14,184,448 B, S=552, D=1, K=20.887491, points=65.994313. **LATEST**; **BEST** remains `run-804f529ac682` (K=20.892890).


## Official board result — commit c096950 (2026-10-31 23:55:08 UTC)

Run `run-df2932b2ba2d`; all five gates passed. T=0.073738 s, M=14,114,816 B, S=552, D=1, K=21.029207, points=66.141145. This is **BEST at this run**, improving prior BEST `run-804f529ac682` (K=20.892890); source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`.

## Mainline 128-shard candidate — official validation pending

Candidate source blob `a9b2c765efe2a5fedec7671d9df9be77a700c853` from C main retains the guarded AVX2/SSE2 quote scanner and increases the name-index shard count from 64 to 128. Exact full-seed and holdout references, adversarial overflow/collision tests, ASan/UBSan/TSan, pinned offline Docker and sandbox passed in CI `41248440108` (both attempts). Two paired 12-trial full-PGO developer-runner comparisons against the AVX2 predecessor estimated complete-K proxies +1.67% and +2.34%, with RSS unchanged; official formatter S, cgroup M and scoring-box K remain decisive. Dockerfile and .speed-demon.toml exactly match the official C build configuration. Official run `run-a7994e398a53` passed every gate but scored K=20.949035 versus BEST K=21.029207, so it is not promoted.


## Official board result — commit 7dc6a03 (2026-10-31 23:58:28 UTC)

Run `run-9e82b6bece9f`; all five gates passed. T=0.072863 s, M=19,316,736 B, S=577, D=1, K=19.736850, points=64.763892. **LATEST**; **BEST** remains `run-df2932b2ba2d` (K=21.029207). The 128-shard mainline candidate was rejected: despite a faster T than C BEST, formatted size and memory rose materially and K regressed. Restore the C BEST source from parent `c096950` after the next frontier trial.

## Frontier PR #12 — scored, not promoted

Imported only PR #12 source blob `8bee2ee3a2cb027098f5b95a4279bfb9a30da785`; it exactly matches the source tested by successful CI `41251942615` (run head `90da546`). The run passed full seed-1/holdout references, ASan/UBSan, TSan, page-tail/collision/overflow cases, pinned offline Docker and sandbox. Developer reports: pinned GCC15 PGO 68.679→59.927 ms against main and 72.254→60.703 ms against its official-BEST baseline; paired restricted-container median 145.858→129.350 ms, cgroup peak 10.168→10.150 MB. S rose 577→622, D=1; reported complete-K proxy +5% against main. These are development measurements, not board T/M/S/D/K. The previous C BEST remains in parent `c096950` for rollback; PR #12 remains open until official promotion.


## Official board result — commit f8cfd3d (2026-11-01 00:10:50 UTC)

Run `run-a7994e398a53`; all five gates passed. T=0.060680 s, M=21,413,888 B, S=622, D=1, K=20.949035, points=66.058201. **LATEST**; **BEST** remains `run-df2932b2ba2d` (K=21.029207). PR #12’s large runtime gain did not offset its higher memory and source-size axes, so it is not promoted. Restore the known-good C source blob `59974fd6328c2fabb1154ac4cc31bda1036bc6ca`; retain the PR branch open for any developer follow-up.


## Official board result — commit eeef411 (2026-11-01 00:17:52 UTC)

Run `run-0ceea23832a5`; all five gates passed. T=0.074715 s, M=14,336,000 B, S=552, D=1, K=20.826396, points=65.930706. **LATEST**; **BEST** remains `run-df2932b2ba2d` (K=21.029207).

## Official board result — commit d1cb0e5 (2026-11-01 00:22:52 UTC)

Run `run-babf3d2dbe5f`; all five gates passed. T=0.074347 s, M=16,474,112 B, S=552, D=1, K=20.305397, points=65.380574. **LATEST**; **BEST** remains `run-df2932b2ba2d` (K=21.029207).

## Official board result — commit cf46ad7 (2026-11-01 00:32:52 UTC)

Run `run-0c7514c8de3b`; all five gates passed. T=0.074028 s, M=14,118,912 B, S=552, D=1, K=20.986758, points=66.097268. **LATEST**; **BEST** remains `run-df2932b2ba2d` (K=21.029207).

## PR #12 retest superseded; PR #13 frontier trial — pending

PR #12's prior official `run-a7994e398a53` passed all gates at K=20.949035, 0.38% below BEST; its planned repeat on queued commit `b40d017` was superseded before dispatch when a stronger, newer frontier candidate arrived. PR #13 source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` at head `e5d6fadec60f9a4948d49ff0bd7d78511f78616c` passed CI `41255591511` on the exact same source blob (`f0b0434`): full seed-1, full seeds 11/29 x3, hostile/overflow/long/EOF tests, ASan/UBSan, TSan, pinned offline Docker and unprivileged sandbox. It compacts name metadata 24→16 B and pending rows 56→48 B, delaying exact key verification across a batched prefetch phase. Paired GCC15 full-PGO medians improved 97.498→85.557 ms over PR #12 (+12.25%); cgroup peak was 10,473,472→10,498,048 B (+24,576 B), S=622→637, D=1, and the developer complete-runner K proxy was +6.3%. These are not official scoring-box T/M/S/D/K. A local static host compile also passed (1,133,320-byte binary). Dockerfile and `.speed-demon.toml` blobs exactly match the official C configuration. This stronger tested candidate replaces the queued PR #12 source for official validation; no promotion until its official run and all gates are confirmed. Parent `cf46ad7` preserves the C champion for rollback.


## Official board result and promoted frontier — commit b665afd (2026-11-01 00:37:52 UTC)

Run `run-f24670761e6b`; all five gates passed. T=0.056051 s, M=21,225,472 B, S=637, D=1, K=21.757571, points=66.880520. **BEST = LATEST**, improving `run-df2932b2ba2d` (K=21.029207) by 3.46%. This validates and promotes PR #13 source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`; its full candidate evidence and rollback reference are above. PR #13 is not yet merged into developer main: main advanced to `bc38ad0` after the PR branch and currently conflicts in `track-c/join.cpp` and `tests/qualify_frontier.py`. Preserve the verified official source while the developer resolves/rebases the conflicting main experiment; do not overwrite either source.

## Current C main trial — official validation pending

Imported the exact `track-c/join.cpp` blob from current C main `bc38ad0921addb4492fa633f7f301e6b1f7c7026` (EOF-safe padded short-name CRC32C). Developer workflow `41257509982` passed exact references on full seeds 1, 11 and 29, hostile/page-tail cases, ASan/UBSan, TSan, pinned offline Docker, and the full official hash. Its 12 paired full-PGO trials report median 127.008→114.708 ms (9.68% faster) and median RSS unchanged at 16,588 KiB; these are development evidence, not official score axes. Exact source compiles here with official static flags; Dockerfile SHA-256 matches C main. The prior C frontier PR #13 BEST remains the rollback candidate pending official K for this trial.


## Official board result — commit 925095f (2026-11-01 00:42:54 UTC)

Run `run-0c2030ee4c92`; all five gates passed. T=0.062880 s, M=21,475,328 B, S=597, D=1, K=20.694460, points=65.792705. **LATEST**; **BEST** remains PR #13 run `run-f24670761e6b` (K=21.757571). The EOF-safe mainline hash trial is rejected: official K is 4.89% below the PR #13 BEST despite its developer PGO runtime gain. Restore exact PR #13 source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`, now merged into C main as `da7fe7bd83802ea10e5030c3e45983d495bddb9c`; this is the next C rollback/qualification candidate.


## Official result after PR #13 merge — commit 16126e3 (2026-11-01 00:47:54 UTC)

Run `run-66ac512b88eb`; all five gates passed. T=0.056216 s, M=21,155,840 B, S=637, D=1, K=21.739900, points=66.862877. This is the merged PR #13 source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`; **LATEST**, while **BEST** remains `run-f24670761e6b` (K=21.757571). The result is within 0.1% of BEST; retain as champion source.


## Official board result — commit 12673d7 (2026-11-01 00:52:54 UTC)

Run `run-678c494ba7f1`; all five gates passed. T=0.056720 s, M=21,118,976 B, S=637, D=1, K=21.650647, points=66.773544. **LATEST**; **BEST** remains `run-f24670761e6b` (K=21.757571), source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`.


## Official board result — commit 32bcf03 (2026-11-01 00:57:54 UTC)

Run `run-7b727e81c6cd`; all five gates passed. T=0.056894 s, M=21,000,192 B, S=637, D=1, K=21.641914, points=66.764784. **LATEST**; **BEST** remains `run-f24670761e6b` (K=21.757571). C source remained PR #13 blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`.

## Official board result — commit 033819b (2026-11-01 01:02:54 UTC)

Run `run-181942cb429e`; all five gates passed. T=0.055956 s, M=21,192,704 B, S=637, D=1, K=21.782763, points=66.905648. **BEST = LATEST**, a 0.12% gain over `run-f24670761e6b` (K=21.757571); source remained safe PR #13 blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. This small delta is within likely run variance.

## Current-main candidate queued for official validation (2026-11-01)

Imported only `track-c/join.cpp` from current verified C main commit `75b53274eb5d05ee7e53ecc66d09daef7ae36546`, source blob `b4b9042a69f293e37acbe0a9b31dd60a3063be22`; retains the safe EOF guards and adds demand-driven half-shard name-slot allocation plus write-membership prefetch. CI `41259282478` passed references, ASan/UBSan, TSan, hostile/collision/overflow and page-aligned EOF tests, offline Docker and sandbox. Full-PGO paired timing versus the qualified short-path control improved 93.197→82.046 ms (RSS 30,352→30,082 KiB); pinned-compiler PGO improved 84.716→81.039 ms (RSS 29,960→35,548 KiB); a separate full-PGO architecture pair was 80.452→81.179 ms. Restricted-cgroup median was effectively flat at 10,487,808→10,485,760 B. Mixed controls and RSS variance make the official run decisive; these are developer CI measurements, not official axes. **Official run `run-bb97a1fb9da0` on commit `832a496`: T=0.059548 s, M=21,655,552 B, S=637, D=1, K=21.024522, points=66.136306; all five gates passed. This is 3.48% below current BEST `run-181942cb429e` (K=21.782763), so the candidate is not promoted after this run; source restored from parent `e7de03a`. Previous C source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` remains in parent `e7de03a` for rollback.


## Official board result — commit 832a496 (2026-11-01 01:07:54 UTC)

Run `run-bb97a1fb9da0`; all five gates passed. The C candidate source was blob `b4b9042a69f293e37acbe0a9b31dd60a3063be22`; **LATEST** K=21.024522, versus **BEST** `run-181942cb429e` K=21.782763 on safe PR #13 source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. Because the candidate missed BEST and its CI speed advantage was mixed across controls, restore the exact PR #13 source; retain the tested candidate in parent `832a496` for rollback/retest.

## New current-main C candidate; official validation queued (2026-11-01)

Imported only `track-c/join.cpp` from current C main commit `0ce09e247fa438e5c9eceaf287ba01a8e1c7303a`, source blob `499944e542a384526eace9d9c94038791a8ecf3b`. Its CI `41259602337` passed full/tiny/sample references, page-aligned EOF and hostile collision/overflow cases, ASan/UBSan, TSan, pinned offline Docker and sandbox. Paired full PGO against the qualified safe champion: 110.737→81.139 ms, but process RSS 16,956→41,314 KiB; separate pinned PGO: 85.985→80.412 ms and RSS 35,720→30,402 KiB. Ordinary full-scale runtime was flat at 88.503→88.495 ms. Restricted-cgroup median was 10,493,952→10,496,000 B (+2,048 B); another control improved 91.731→82.108 ms while process RSS fell. **These mixed developer controls justify one official trial, not promotion.** Exact submission C++17 build succeeds; **official T/M/S/D/K pending**. Rollback source remains `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` in official history before this candidate.


## Official board result — commit bc48c37 (2026-11-01 01:12:54 UTC)

Run `run-b5b6c8351a7a`; all five gates passed on candidate source blob `499944e542a384526eace9d9c94038791a8ecf3b` from C main `0ce09e2`. T=0.056770 s, M=20,885,504 B, S=649, D=1, K=21.628646, points=66.751467. **LATEST**; **BEST** remains `run-181942cb429e` (K=21.782763) on safe PR #13 source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. Candidate reduced M by ~1.4% but increased S by 12 and did not improve T/K; not promoted, restore PR #13 source from parent `74baa2c`. Keep this exact main candidate in commit `bc48c37` for rollback/retest.


## Official board result — commit 62c5bf4 (2026-11-01 01:17:54 UTC)

Run `run-3a336d8f9e98`; all five gates passed on restored PR #13 source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. T=0.056845 s, M=23,330,816 B, S=637, D=1, K=21.200272, points=66.317072. **LATEST**; **BEST** remains `run-181942cb429e` (K=21.782763).


## Current-main parser candidate queued after CI (2026-11-01)

Source blob `3519869c67493e3e5da7c4ced30b38be438cfeca` from C main commit `942a040d57520768449281de1752582d17f99fa1`, the branchless mixed-newline parser. CI `41259948744` passed all references, page-aligned EOF, hostile fixtures, ASan/UBSan, TSan, pinned offline Docker and sandbox. Against the qualified safe champion, full-scale paired timing was 89.897→84.509 ms (process RSS 43,510→44,258 KiB); pinned PGO 82.500→78.786 ms (RSS 35,352→41,404 KiB); full-PGO 80.807→79.011 ms; official-BEST architecture 80.754→80.135 ms; short-path control 91.990→79.389 ms. The paired restricted-cgroup median was 10,496,000→10,498,048 B (+2 KiB); source falls from 545 to 534 lines, while official S is unmeasured. These measurements justified an official trial. The exact-source official results are in the later board receipts; both runs remained below the safe PR #13 BEST. Safe PR #13 source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` remains in earlier commits for rollback.


## Official board result — commit d411050 (2026-11-01 01:22:54 UTC)

Run `run-994f040e654c`; all five gates passed on current C main source `3519869c67493e3e5da7c4ced30b38be438cfeca`. T=0.056477 s, M=21,401,600 B, S=646, D=1, K=21.594072, points=66.716727. **LATEST**; **BEST** remains `run-181942cb429e` (K=21.782763) on safe PR #13 source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. This candidate improves the low-scoring restored-source rerun `run-3a336d8f9e98` (K=21.200272), but remains 0.87% below BEST and increases S by 9. The exact-source repeat on commit `132ef00` scored K=21.666835; the candidate is not promoted. PR #13 remains the selected C source.


## Official board result — commit 132ef00 (2026-11-01 04:06:36 UTC)

Run `run-dbb1df252c28`; all five gates passed on source `3519869c67493e3e5da7c4ced30b38be438cfeca`. T=0.056258 s, M=21,250,048 B, S=646, D=1, K=21.666835, points=66.789774. **LATEST**; **BEST** remains `run-181942cb429e` (K=21.782763).

## C main candidate result — not promoted

Imported only `track-c/join.cpp` from latest C main `e0982830d2d86cee090ec6d8d332d55450dba455`, source blob `b31de39258eec335f79e14a0568a325d4ad2c732`. This is the twice-qualified parse-stage name lookup/membership-prefetch source. CI `41261183692` passed full seed-1/holdout exactness, hostile cases, ASan/UBSan/TSan, pinned offline Docker and sandbox. Paired full-PGO 12-trial comparisons against current official-source candidate `3519869c`: 65.070→64.236 ms and 78.833→77.788 ms; cgroup peaks 10,487,808→10,473,472 B and 10,498,048→10,467,328 B; formatted lines 544→543. Runner K proxies improved 0.70%/0.76%; source-only timings regressed, so evidence applies to the pinned PGO release. Official result is recorded below; this source did not promote. The previously measured PR #13 BEST remains the selected C source.

## Official validation of C main candidate — commit 4a4461e (2026-11-01 04:11:36 UTC)

Run `run-440557638313`; all five gates passed on C main blob `b31de39258eec335f79e14a0568a325d4ad2c732`. T=0.055865 s, M=23,912,448 B, S=644, D=1, K=21.245497, points=66.363344. **LATEST**; **BEST** remains PR #13 run `run-181942cb429e` (K=21.782763). This candidate trails BEST by 2.47% and trails the prior exact-source run of `3519869c` (K=21.666835); it does not promote. Restore PR #13’s measured best source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`; the prior official commit retains the tested main candidate for rollback.

## Selected source restored before next official validation

Set `track-c/join.cpp` back to exact PR #13 BEST blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` (PR head `e5d6fadec60f9a4948d49ff0bd7d78511f78616c`), replacing C main blob `b31de39258eec335f79e14a0568a325d4ad2c732` that produced `run-440557638313`. The selected source was previously official BEST at `run-181942cb429e`; the changed main candidate failed to beat it on the current run. Production-flag local compile succeeded. The next pushed commit will revalidate this exact source along with the selected B candidate.

## Official board result — restored PR #13 source, commit a13b5ef (2026-11-01 04:16:46 UTC)

Run `run-0a28df8c793f`; all five gates passed on exact source blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a`. T=0.057303 s, M=21,258,240 B, S=637, D=1, K=21.511932, points=66.633971. **LATEST**; **BEST** remains `run-181942cb429e` (K=21.782763), same source. The restored champion is 1.24% below its prior BEST reading, but 1.25% above the discarded C main candidate’s latest K=21.245497.
Sequential official result after switching from C main blob `b31de...` (`run-440557638313`) to restored PR #13 blob `c4b414...` (`run-0a28df8c793f`): K 21.245497→21.511932 (+1.25%), M 23,912,448→21,258,240 B (-11.10%), S 644→637; T changed 0.055865→0.057303 s. These are sequential board trials, not a controlled A/B; **BEST** remains 21.782763 on the same restored source.

## C valid-CSV frontier official validation (2026-11-01)

Imported only `track-c/join.cpp` from `sd-tc/frontier/c-valid-csv-frame` at branch head `cba12d3a51b275a1abf440718524901cd3887698`, exact source blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. The 14-add/10-delete source diff consumes promised well-formed CSV delimiters directly in release while retaining debug assertions; quoted fields, numeric fallbacks, CRLF/LF, BOM and optional final EOF remain handled. Developer CI `41259335164` passed verify and ASan/UBSan plus TSan. Twelve randomized pinned-GCC15 PGO trials in a restricted 2-CPU container reported wall 106.682→105.738 ms (-0.89%), CPU 238.778→217.303 ms (-8.98%), memory 10,153,984→10,170,368 B (+16 KiB); local full-seed-1 hashes were exact. These are developer measurements, not official board axes. The source compiles locally with official C++17 flags. Official board result is recorded below; the exact source remains the PR #13 known-good blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` in the preceding official commit as rollback.

## C valid-CSV frontier official promotion — commit 0e56118 (2026-11-01 04:23:34 UTC)

Run `run-d6f721bba982`; all five gates passed on source blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.054110 s, M=21,049,344 B, S=637, D=1, K=22.181304, points=67.299354. **BEST at this run**, improving prior BEST `run-181942cb429e` (K=21.782763) by 1.83%, and the exact PR #13 source's immediately prior run `run-0a28df8c793f` (K=21.511932) by 3.11%. The frontier source passed board build, correctness, timeout and sandbox gates; promote it in the official repo. Rollback to known-good PR #13 blob `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` remains in the previous official commit. No developer PR exists for this frontier branch, so there is no PR to merge.

## Official board result — commit f281e05 (2026-11-01 04:30:02 UTC)

Run `run-893aa05f3cdc`; all five gates passed on the same valid-CSV frontier blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.063932 s, M=21,389,312 B, S=637, D=1, K=20.341129, points=65.418753. **LATEST**; **BEST** remains `run-d6f721bba982` (K=22.181304), on the same source. This repeat is 8.30% lower in K, with T +18.18% and M +1.62% versus that prior run; all correctness/build/sandbox gates still passed. The same C source is selected in the official tree, but this spread is materially larger than A/D repeats and needs another official measurement before final freeze. Build time was 18.373 s for `run-d6f721bba982` and 0.931 s for `run-893aa05f3cdc`; build time is reported separately from T, so the 18.18% T spread is not a build-time difference.

## Official board result — commit 1633378 (2026-11-01 04:36:05 UTC)

Run `run-65aa384d609d`; all five gates passed on the unchanged valid-CSV frontier source blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.054927 s, M=21,409,792 B, S=637, D=1, K=21.941087, points=67.062907. **LATEST**; **BEST** remains `run-d6f721bba982` (K=22.181304) on this same source. Relative to the prior same-source run `run-893aa05f3cdc`, K rose 7.87%, T fell 14.08%, and M rose 20,480 B. The third reading is 1.08% below BEST and shows the prior low was not repeated; retain the tested frontier source and its PR #13 rollback.

## Official board result — commit 116914f (2026-11-01 04:41:53 UTC)

Run `run-f80ed1ab9d5f`; all five gates passed on unchanged valid-CSV frontier source blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.066847 s, M=21,569,536 B, S=637, D=1, K=19.859323, points=64.898222. **LATEST**; **BEST** remains `run-d6f721bba982` (K=22.181304) on this same source. Compared with `run-65aa384d609d`, K fell 9.49%, T rose 21.65%, and M rose 1.59%; no C source changed between these runs. Keep the exact PR #13 rollback source `c4b41459c8ce1ea8d47e834a136cb9d11b73cd2a` in prior commits while gathering a controlled baseline if further C changes are considered.

## Official board result — commit b5b3fec (2026-11-01 04:47:45 UTC)

Run `run-4a93944b104c`; all five gates passed on unchanged valid-CSV frontier blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.054248 s, M=21,164,032 B, S=637, D=1, K=22.129012, points=67.248101. **LATEST**; **BEST** remains `run-d6f721bba982` (K=22.181304) on the same source. Relative to `run-f80ed1ab9d5f`, K rose 11.43%, T fell 18.83%, and M fell 1.88%; C source was unchanged. This near-BEST result reinforces the need to distinguish source performance from noisy board repeats.

## Official board result — commit de9c67e (2026-11-01 04:53:02 UTC)

Run `run-45f06d79e387`; all five gates passed on unchanged valid-CSV frontier blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. T=0.055624 s, M=23,404,544 B, S=637, D=1, K=21.418173, points=66.539121. **LATEST**; **BEST** remains `run-d6f721bba982` (K=22.181304) on this same source. Compared with `run-4a93944b104c`, K fell 3.21%, T rose 2.54%, M rose 10.58%; no C source changed. Keep the PR #13 rollback in prior commits.

## Fresh text-pair/name-key frontier PR #14 (2026-11-01)

- Testing the exact PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`; no adaptations. This is based on C main source blob `b31de39258eec335f79e14a0568a325d4ad2c732`, while the then-current official C source was the separate valid-CSV frontier blob `be24e4ddc71817de5b5bc94ab4285ebc8d972bf6`. Its exact official score will determine promotion.
- Exact official static C++17 compile passed locally. [CI 41274929908](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41274929908) passed exact differential/full-seed references, wide-region-ID fixtures, ASan/UBSan, TSan, pinned offline Docker, unprivileged sandbox, paired pinned/full-PGO and cgroup comparisons.
- Developer's two interleaved local PGO batches report complete K proxy +2.6–4.4% over main and +2.9–4.2% over the prior official PR13 source; cgroup memory increased about 0.4 MB. These are developer measurements, not board scores. BEST before this trial remains `run-d6f721bba982` (K=22.181304) on `be24e4dd`.
- Official board result and promotion decision: pending.

- Promoted PR #14 after official run `run-6b1f74906d40` on exact source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`; all five board gates passed. Official metrics: T=0.050537 s, M=11,612,160 B, S=657, D=1, K=25.731929, points=70.523617. **LATEST and BEST** (replaces `run-d6f721bba982`, K=22.181304). Against the immediately preceding official `be24e4dd` run `run-4a93944b104c`, K improves 16.28%, T improves 6.84%, and M falls 45.14%; S increases 20 lines, D unchanged. The PR merged into C main as `d459dccbe2a4145e60bc19791a1b0bca14ba12d6`.
- Post-merge `main` workflow [41275332278](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41275332278) also completed successfully on merge commit `d459dccbe2a4145e60bc19791a1b0bca14ba12d6`.

- Repeat official run on source-identical commit `6917275dbd2ee12fd19df6fe3b87a60920c86ef8`: `run-e7eab9673214`, all five gates passed. T=0.050141 s, M=11,288,576 B, S=657, D=1, K=25.979773, points=70.731767. **LATEST and BEST**, 0.96% above previous C run `run-6b1f74906d40` and 17.12% above the pre-PR14 BEST `run-d6f721bba982` (K=22.181304). Exact C source unchanged.

- Repeat official run on source-identical commit `17a6d96ba2cf813bac7eea2225b51fdd4d34960a`: `run-109cf5cfcfa7`, all five gates passed. T=0.050575 s, M=11,902,976 B, S=657, D=1, K=25.595323, points=70.408031. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). Same source, within 1.48% of its repeat BEST and 15.39% above pre-PR14 BEST `run-d6f721bba982` (K=22.181304).

## Recent private-reconciliation architecture PRs (not promoted; 2026-11-01)

- PR #16 (`frontier/c-private-epoch-20261101`, head `07cf45ba`) passed correctness, ASan/UBSan, TSan, pinned offline Docker, sandbox and independent full-seed CI `41280672480`. Its paired developer full-PGO comparison against the qualified fused scanner regressed 65.212→112.747 ms; median cgroup peak rose 11,042,816→14,295,040 B and S 657→725. Reject; do not dispatch or merge.
- PR #17 (`frontier/c-private-tile-20261101`, head `9603aa6a`) passed the same categories in CI `41281228501`, but paired full-PGO time regressed 76.962→103.837 ms and median cgroup peak rose 11,046,912→14,960,640 B; the final serial distinct reduction costs ~6 ms. Reject; do not dispatch or merge.
- These are developer-runner measurements, not official board axes/K. Retain PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`; official C BEST remains `run-e7eab9673214` (K=25.979773).

- Official run on `0d48c0b1302610385c4608b30b6842aa71e388cb`: `run-186c50518300`, all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.067444 s, M=11,845,632 B, S=657, D=1, K=22.185865, points=67.303818. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). The previous three same-source C results were K=25.731929, 25.979773 and 25.595323; this low repeat coincided with lower K on A/B/D and no source changes. Preserve the proven PR #14 candidate; do not infer a source regression from this single run.

- Official run `run-f94d784743fe` on checkpoint `b70956dd71a72aec0c5bace4f41dcf3a9807f8ba`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.050197 s, M=11,722,752 B, S=657, D=1, K=25.770027, points=70.555744. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). This is another source-identical confirmation near the prior three official measurements (K=25.595323–25.979773); no C source change.

- Official run `run-ef82fbfdaa9b` on `dde14ac917c8ad8642c734162b25804a4008cc90`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.051580 s, M=11,849,728 B, S=657, D=1, K=25.367480, points=70.213866. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

- Official run `run-767591df0369` on `346a17e08d7356487484b804bbd9a0a456bfa4f5`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.050969 s, M=11,735,040 B, S=657, D=1, K=25.568762, points=70.385485. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

- Official run `run-e52558b85ff3` on rollback checkpoint `d3af7efd6ac8fd8982cbaae3b759052ccd74547f`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.050821 s, M=12,005,376 B, S=657, D=1, K=25.489594, points=70.318146. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

- Official run `run-22bb02617815` on `bf2de0f901f0e5bc2e1dc07331fd0de0622ff400`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.067609 s, M=11,505,664 B, S=657, D=1, K=22.288204, points=67.403754. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). This is a low same-source result; compare the repeated official PR #14 runs before attributing it to code.

- Official run `run-f55de9bd6fa6` on `82d831033431c94a929d3c0eb99d62a0d061583a`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.050291 s, M=11,730,944 B, S=657, D=1, K=25.742335, points=70.532397. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

- Official run `run-b625ade658c6` on `227bae88c5b80d003fdc3dda193ae499ffc8f66e`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.050779 s, M=11,620,352 B, S=657, D=1, K=25.666919, points=70.468687. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

- Official run `run-f020e91bc766` on `dbbef62bc1668f45d4544f8fde7cb6c758996b68`; all five gates passed on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. T=0.051028 s, M=11,513,856 B, S=657, D=1, K=25.651410, points=70.455562. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).


- Follow-up official run `run-5952fe93a7c7` on commit `01966dd4c4464d08d4c2a5e44518a351cb102d07` passed all five gates on unchanged promoted PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.052228 s, M=12,148,736 B, S=657, D=1, K=25.084287, points=69.970088. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). Other tracks also scored below their same-source BESTs on this dispatch, so retain BEST and do not attribute the repeat delta to source.


- Official run `run-471e7854999d` on commit `8c51ca2873b18b633fce3f1772a3c6a1a6359b32` passed all five gates on unchanged PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.050367 s, M=11,796,480 B, S=657, D=1, K=25.694262, points=70.491807. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).


## C PR #19 inline16 exact-name repair — skipped after CI comparison

- Exact-head CI [41292530501](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41292530501) passed correctness, hostile fixtures, ASan/UBSan, TSan, pinned offline Docker/sandbox and PGO compilation.
- The relevant paired full-PGO comparison against the qualified official source measured 77.472 ms baseline versus 85.801 ms candidate (+10.75% slower); cgroup median improved 11,026,432 to 9,977,856 B. The source-only comparison also regressed 85.623 to 100.694 ms. The 95.517→85.467 ms PGO comparison was profiled versus unprofiled builds of the same candidate, not a candidate-versus-champion gain.
- Despite a positive local two-CPU result, the exact CI head-to-head is negative and the larger source has no official S/K measurement. Do not dispatch or merge PR #19; restore the qualified PR #14 source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`.


## Official rollback checkpoint `cf650cc` — C PR #14 source confirmed

- Board run `run-41637ed4f1a1` on commit `cf650cc6b47038ae06fdf208279d68e2c14355aa` passed all five gates on selected C PR #14 blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.066052 s, M=11,395,072 B, S=657, D=1, K=22.592967, points=67.698664. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). Simultaneous cross-track declines on this dispatch indicate board variance; preserve the qualified source.

## C main sixteen-row batch trial — rejected on paired CI evidence

- Exact-head CI [41293459256](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41293459256) passed correctness, sanitizers, Docker/sandbox and full-reference checks for commit `95874a5c59c41df5a8c086f18c39cb371ff356bf`. Its paired full-PGO median was 77.129 ms versus 75.955 ms for the 32-row qualified source (+1.55% slower); cgroup medians were 11,024,384 versus 11,028,480 B (effectively unchanged). No complete-K evidence justified a board dispatch, so main restored the 32-row source.

## C PR #20 private radix ownership — skipped, exact CI regressed

- Draft PR #20 exact-head CI [41293115199](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41293115199) passed correctness, ASan/UBSan, TSan, full references and pinned offline Docker/sandbox checks. The relevant paired full-PGO median was 93.112 ms versus 76.947 ms for the official source (+21.0%); peak RSS was 208,392 versus 36,800 KiB. Cgroup median was 12,597,248 versus 11,034,624 B (+14.2%). Despite promising native local timings, these exact CI regressions and missing complete-K evidence do not justify an official trial. Do not promote or merge; retain PR #14 blob `0772ace04e358868f0b060b178d6ab77e93a15ab`.


## Official run `5f15f25` — C PR #14 source

- Board run `run-e50afc3730a2` on commit `5f15f2543fbd6a9e18fc3f80490190399322a13d` passed all gates on C blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.050964 s, M=11,948,032 B, S=657, D=1, K=25.478194, points=70.308432. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). C source did not change.

## Official run `488ee43` — selected C PR #14 source

- Board run `run-97837456b295` on commit `488ee43f787334f7c89060ebaaa785e069ea5982` passed all gates on unchanged C blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.050322 s, M=11,907,072 B, S=657, D=1, K=25.657819, points=70.461023. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). No C source change.

## Official rollback `4b31a19` — selected C PR #14 source

- Board run `run-4e3efc33086b` on commit `4b31a195a1c7c4296ca7c3442e774fb9e3e59f91` passed all five gates on unchanged blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.051140 s, M=11,825,152 B, S=657, D=1, K=25.486956, points=70.315898. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

## C development-main fast-path candidate — official scorer trial

- Imported exact source blob `3b5e1392f49abdbb7fdcf6a36b5866366298143b` from current developer main `32c6bfeba97fdae8de9722bb334df54949ceb395`; rollback is qualified official blob `0772ace04e358868f0b060b178d6ab77e93a15ab`. Dockerfile is byte-identical; no additional dependencies.
- The in-mask simple-quote path reuses the first 64-byte AVX2 quote mask to bypass PCLMUL only when quote/comma boundaries certify two quoted, unescaped fields; escaped quotes, long/unquoted fields retain the exact fallback.
- Exact-source CI `41298153512` passed full seed-1 SHA-256, holdouts 11/29 repeated three times, hostile quote-boundary/collision/overflow tests, ASan/UBSan/TSan, pinned offline Docker and sandbox.
- Two direct full-PGO paired studies: 77.017→75.639 ms (11/12 faster) and independent 82.285→80.238 ms (11/12 faster). Cgroup peaks 10,993,664→11,026,432 B and 11,016,192→11,036,672 B; physical source 540→567 lines. Complete-K runner proxies +0.11%/+0.49%; official scoring-box T/M/S/D/K pending. Run through the official scorer before promotion.

## C developer-main candidate `5f00315` — rejected on official score, champion restored

- Board run `run-1021b421c2ee` on commit `5f00315f8696ca1853c5fb927ad5cd447c6253e9` passed all five gates on exact main-source blob `3b5e1392f49abdbb7fdcf6a36b5866366298143b`: T=0.065087 s, M=11,567,104 B, S=669, D=1, K=22.630206, points=67.734425. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).
- Despite two exact-source paired full-PGO CI comparisons showing 1.8–2.5% faster and clean correctness/sanitizer/Docker gates, the official candidate was 29.8% slower than BEST, used 2.5% more memory, and had 12 more scored source units. It loses K by 12.9%; reject. Restore prior champion blob `0772ace04e358868f0b060b178d6ab77e93a15ab` and retain it as rollback.

## Official C rollback `9ded4d1` — selected PR #14 source

- Board run `run-e4aa47ede1a3` passed all gates on restored blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.050424 s, M=11,771,904 B, S=657, D=1, K=25.690448, points=70.488584. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

## C seed-1 PGO training follow-up — not dispatched

- Exact-head CI [41306717074](https://github.com/insightlabs38-pixel/sd-tc/actions/runs/41306717074) passed full/sample/tiny hashes, full holdouts 11/29, ASan/UBSan, TSan, pinned offline Docker and sandbox for main commit `aacb36be8c8eb9d31eb67d61c43546891a3be2eb`; its source remains blob `3b5e1392f49abdbb7fdcf6a36b5866366298143b`, while Docker training changes seed 37 to seed 1.
- Paired full-PGO seed-37→seed-1 medians were 105.487→104.945 ms (-0.51%); cgroup medians 11,018,240→11,024,384 B (+6,144 B). This small runner-only effect does not justify another board run after the same source scored K=22.630206 on the official box. Keep the official champion; no PGO seed change imported.

## Official evidence refresh `5d08af1` — selected C source

- `run-7ecb0d605658` passed all gates on unchanged C blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.053177 s, M=11,882,496 B, S=657, D=1, K=24.969867, points=69.870811. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773). Keep the selected C source; same-source K variation is substantial.

## Official evidence refresh `89fb2f8` — selected C source

- `run-28f2633cb497` passed all gates on unchanged C blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: T=0.050366 s, M=11,620,352 B, S=657, D=1, K=25.771938, points=70.557354. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

## Team-wide official evaluation `163279d` — unchanged C source

- Source blob `0772ace04e358868f0b060b178d6ab77e93a15ab`: run `run-e15bc2903994` passed all five gates, T=0.050528 s, M=11,808,768 B, S=657, D=1, K=25.647952. **LATEST**; **BEST** remains `run-e7eab9673214` (K=25.979773).

## C frontier PR #20 private radix ownership — deferred pending complete K

- Draft head `bf3052fbce35240010a5d0c74ab854f7d05412f9`; exact PR checks for verification, ASan/UBSan and TSan pass. Reported pinned full-PGO time is 152.026 ms vs 156.468 ms (-2.8%), while median cgroup peak is 12.45 MiB vs 10.95 MiB (+13.7%). The handoff says complete K and CI scaling remain under evaluation; source-size/K tradeoff is therefore unresolved. Do not dispatch or promote until those measurements establish a net score opportunity.
