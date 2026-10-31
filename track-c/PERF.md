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
