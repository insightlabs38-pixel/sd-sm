# Track D evidence

- **Current champion:** 64-bit radix heap, exact forward-CSR probe (256 settled vertices) followed by directed bidirectional Dijkstra with dual CSR; four independent workers, no third-party runtime dependencies.
- **Official full seed 1:** graph/queries SHA-256 match organizer-published hashes; output `a23dbdf0a3e49cc8901310a9ee1dc6a9a569a85297b6da75c2a7002cb2ed277e` matches exactly. Native GitHub-hosted runner: **1.35 s elapsed, 263,840 KiB peak RSS**. These are not scoring-box measurements.
- **Official sample seeds 1 and 2, tiny seed 2:** output byte-for-byte matches the organizer's Python reference. The official worked example matches SHA-256 `2e9871bba1d5013144ceff48d806a28da0e3f203b29118a89d98d8f654c3f6a0`.
- **Docker:** allowlisted digest-pinned GCC 15 build + Debian 13 runtime, static binary; network-disabled/read-only Docker executions match native reference on sample and full seed 1. [Successful full qualification](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41085036796).
- **Independent tests:** 83 differential fixtures across one-/two-pass parsing and 1/4 workers, plus a separate 500-seed stress sweep; ASan/UBSan pass. A 176,410-node independent synthetic graph matches the Python oracle (SHA-256 `7ecd1c595ca370bcdf8d0526efcb88a597897be6c42a7ed13174dc64c7367fb2`).
- **Local full-size synthetic, not organizer data:** forward binary heap ~6.7 s / 210 MB; bidirectional binary ~4.1–4.5 s / 264 MB; bidirectional radix ~3.6–4.3 s / 264 MB across varying host contention. Radix won repeated matched comparisons; 16-bit stamps and alternative direction policies were not promoted.
- **Official scored board:** no Track D PERF run ID yet; the integrator owns official submission and scored performance verification.

## Luna integration validation, October 30, 2026

- Promoted `sd-td` main HEAD `41ccb500be132b5bc5b53a9fdb9e6ae53c8dffc9`; the prior official D folder was the unchanged starter reference and remains available in parent commit `5f9e356c43e9ad613b75dd0a5c6b6c0376f2e39d` for rollback.
- Independent native full seed-1 execution matched the organizer output SHA-256 `a23dbdf0a3e49cc8901310a9ee1dc6a9a569a85297b6da75c2a7002cb2ed277e`.
- Developer CI [41085036796](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41085036796) passed random/adversarial differential tests, official generated sample/full checks, and the pinned offline Docker runtime/output comparison. It measured 1.35 s and 263,840 KiB peak RSS on a GitHub runner; these are not board values.
- No official board run ID or score exists yet.

## In-place radix redistribution promotion, October 30, 2026

- Candidate `sd-td` main HEAD `a7e34fe89f682e533c39d95bcca064bf36ccbf75`, source blob `480ef00bf57d2431862aa447e014008db335b3eb`; previous official D source remains in release parent `00838f7` for rollback.
- GitHub Actions [41093289804](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41093289804) passed exact full seed-1, differential fixtures and restricted offline Docker on source-identical code. Five-run full-input paired medians: 1.53 to 1.42 s (~7.2% lower); peak RSS 263,716 to 265,504 KiB (~0.7% higher). Native runner measurements, not scoring hardware.
- Redistribution removes the temporary moved vector; no runtime dependency changes. No official board run ID or score is available.

## Eight-bit epochs and early parser scratch release, October 30, 2026

- Candidate: `sd-td` main HEAD `7cc7a0c80880ba6348d381063f5d35231839f904`, source blob `b7ed495b38db2fb1e63165fb8bb1a610e281ae4d`. The candidate blob is identical to the source qualified by CI. Previous official release `1c235c35cc93ea146cf794254eecd56fab8f9948` remains the rollback point.
- Matched seven-run full seed-1 qualification [41110514088](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41110514088) passed the published full output hash, 83 differential cases, 66,000-query epoch-wrap regression, official generated cases, and Docker full-output comparison. Median runtime fell from 1.01 to 0.97 s (4.0%); median peak RSS fell from 238,328 to 227,320 KiB (4.6%). GitHub runner values, not board T/M.
- Eight-bit generation stamps reduce per-query scratch; wrap resets both direction stamps. Parser input scratch is released after CSR construction. No new runtime dependency. The source is 14 physical lines longer than the previous official version.
- Official board BEST/LATEST: unavailable; the team has no registration entry and no board run IDs exist. No official score is claimed.

## Frontier branch review — October 30, 2026

- The exact-mask challenger on `d/epoch8-radix-mask-qualification` passed official full-output, differential, and Docker gates in CI [41132963841], but matched median wall time at 1.32 s, increased RSS 227,320 to 227,356 KiB, and increased source from 308 to 316 counted lines. Estimated K is 0.39% lower; keep `main` source blob `b7ed495b38db2fb1e63165fb8bb1a610e281ae4d`; no open frontier PR or `frontier/*` branch was visible at this check.

## Official board receipts — raw-feed snapshot 2026-10-30 22:52:25 UTC

HighVelocity (`highvelocity-7f330e`) is registered. The watcher reported submission HEAD `3059e71b54cd02e920e995d186a369b4be9c0aeb`, healthy, with no queued or in-flight run at this snapshot. BEST and LATEST are both this successful live-board run; build, check, correctness, sandbox, and timeout gates all passed. These are board IDs, not CI IDs. Earlier “no board run/registration” notes are historical and superseded here.

- **BEST:** `run-336c91d64717`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.709698 s, M=233,807,872 bytes, S=398, D=1, K=9.476251, points=48.831827.
- **LATEST:** `run-336c91d64717`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.709698 s, M=233,807,872 bytes, S=398, D=1, K=9.476251, points=48.831827.


## Official board receipts — raw-feed snapshot 2026-10-30 22:58:54 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher was healthy at `40847ba5fde8714895533f7b47ce8fee48baa09e`, and the dispatch queue was idle after scoring. All five gates (build, check, correctness, sandbox, timeout) passed; failure was null. BEST and LATEST below are the board's records at this snapshot. These board run IDs are distinct from GitHub Actions IDs.

- **BEST:** `run-57cae7f120d3`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=0.692819 s, M=233,615,360 bytes, S=398, D=1, K=9.592570, points=49.096750.
- **LATEST:** `run-57cae7f120d3`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=0.692819 s, M=233,615,360 bytes, S=398, D=1, K=9.592570, points=49.096750.


## Official board results — raw-feed snapshot 2026-10-30 23:10:48 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. The watcher was healthy at `01d4852e1271d5bec3d6de9aaa7641f8616730cb` with an idle queue. Both records passed build, check, correctness, sandbox, and timeout gates; failure was null. These are live-board measurements; BEST and LATEST are separately reported, and run IDs are not GitHub Actions IDs.

- **BEST:** `run-57cae7f120d3`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=0.692819 s, M=233,615,360 bytes, S=398, D=1, K=9.592570, points=49.096750.
- **LATEST:** `run-a95c4d6060eb`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.775566 s, M=233,545,728 bytes, S=398, D=1, K=9.066954, points=47.873070.


## Official board results — raw-feed snapshot 2026-10-31 00:12:03 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. Watcher was healthy at `157f1d478136fd0d7950aa2a82e121c087ec7ec7`, with no queued or in-flight run. Every gate passed; failure was null. These are board measurements, and BEST/LATEST are tracked separately. Board run IDs are not GitHub Actions IDs.

- **BEST:** `run-032e9e3e08f4`; commit `157f1d478136fd0d7950aa2a82e121c087ec7ec7`; T=0.692230 s, M=233,529,344 bytes, S=398, D=1, K=9.597357, points=49.107583.
- **LATEST:** `run-032e9e3e08f4`; commit `157f1d478136fd0d7950aa2a82e121c087ec7ec7`; T=0.692230 s, M=233,529,344 bytes, S=398, D=1, K=9.597357, points=49.107583.


## Official board results — raw-feed snapshot 2026-10-31 00:17:27 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`, queue idle. All five gates passed and failure was null. BEST and LATEST are reported separately; these are live-board IDs, not GitHub Actions IDs.

- **BEST:** `run-f1b186f4e3b3`; commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.691411 s, M=233,517,056 bytes, S=398, D=1, K=9.603141, points=49.120665.
- **LATEST:** `run-f1b186f4e3b3`; commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.691411 s, M=233,517,056 bytes, S=398, D=1, K=9.603141, points=49.120665.


## Official board results — raw feed, 2026-10-31 00:23:55 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `73d8cecee9e50825a4f416b77c11fec448955782`; queue idle. All five gates passed for BEST and LATEST; failure was null.

- **BEST:** `run-f1b186f4e3b3`, commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.691411 s, M=233,517,056 bytes, S=398, D=1, K=9.603141, points=49.120665.
- **LATEST:** `run-905537d84af3`, commit `73d8cecee9e50825a4f416b77c11fec448955782`; T=0.696728 s, M=233,533,440 bytes, S=398, D=1, K=9.566294, points=49.037186.

## Frontier Track D candidate staged for official scoring — October 31, 2026

Candidate from ready PR #1 head `576af9c23bbbdfa16838a4737342ab2063176615`; production source SHA-256 `6143fe3555229c2a180146fc9d8f981d862e9c455f332325b05a1808b7b2a852`. Source-identical CI run [41148832728](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41148832728) passed published full-output hash, differential (83 cases across 3 thread counts and 6 probes), lattice stress, tiny/sample references, ASan/UBSan and pinned Docker. PR reports local 4-core full-seed-1 median T 0.36 s vs 1.10 s and peak RSS 91 MB vs 227 MB; these are not board-hardware results. Pinned source-axis estimate S=708 (prior champion S=398), D=1; applying PR local T/RSS ratios gives estimated K≈18.5 from board BEST K=9.603, not an official score. Native `g++ -O3 -std=c++17 -pthread -flto -static -s` compilation and a directed/zero/large-weight synthetic graph smoke test passed. The local Docker build could not start because `/var/lib/docker/vfs` had no space; source-identical CI run above passed pinned Docker. Awaiting board evaluation. Previous champion and rollback are in parent `73d8cec`.


## Official board results — raw feed observed 2026-10-31 00:29:07 UTC

Watcher was healthy at `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca` (last checked 00:28:14 UTC); queue idle. All five gates passed; failure was null.

- **BEST = LATEST:** `run-acdcbe9eea6a`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.162783 s, M=133,636,096 bytes, S=708, D=1, K=20.297070, points=65.371668.
- Against the previous D BEST (`run-f1b186f4e3b3`: T=0.691411 s, M=233,517,056 bytes, S=398, K=9.603141), this official run is 76.5% faster, uses 42.8% less measured memory, and raises K by 111.4% despite the source-axis increase. This confirms the challenger on board hardware; earlier estimated K≈18.5 was not an official score.


## Official board results — raw feed observed 2026-10-31 00:34:36 UTC

Watcher healthy at `8233a6406105e8580d72bc059d91e48eb88e0868`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST = LATEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.


## Official board results — raw feed observed 2026-10-31 00:40:29 UTC

Watcher healthy at `b6f184e81a93554f4dd2b2e0284258345964f45f`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.
- **LATEST:** `run-19cdd8645901`, commit `b6f184e81a93554f4dd2b2e0284258345964f45f`; T=0.160890 s, M=137,060,352 bytes, S=708, D=1, K=20.313078, points=65.388787.


## Official board results — raw feed observed 2026-10-31 00:46:16 UTC

Watcher healthy at `94a98da3f2e1de31f3b6fc308194c698f3603249`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.
- **LATEST:** `run-21fc19c66290`, commit `94a98da3f2e1de31f3b6fc308194c698f3603249`; T=0.170048 s, M=133,976,064 bytes, S=708, D=1, K=19.848671, points=64.886572.


## Independent developer qualification of the integrated frontier source — October 31, 2026

Track D `main` is now at `83d6bb5`, and its production source blob remains byte-identical to the official source (`aa3a48820bab0a88977b2f19f815ae30964b0850`). CI [41151166030](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41151166030) passed an independent champion/holdout comparison: seven interleaved full-seed-1 runs matched the exact output hash; median T 0.96 to 0.29 s (3.31x), peak RSS 227,320 to 87,944 KiB (61.3% lower), user CPU 2.77 to 0.96 s; full seed 2 and 120 additional lattice stress seeds passed.

A separate 48-run thread/probe sweep [41151731082](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41151731082) passed exact output hashes across 16 configurations. On that GitHub runner, median T/RSS were 0.38 s/87,936 KiB at 4 threads, 0.41 s/89,104 KiB at 6, and 0.45 s/99,960 KiB at 12. These CI measurements support correctness and the current default but are not scoring-box results; official board BEST/LATEST remain the measurements above.


## Official board results — raw feed observed 2026-10-31 00:51:41 UTC

Watcher healthy at `8b137acc1b2f3a83c9b7c422088b7b966357232e`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.
- **LATEST:** `run-6cfbacca3af4`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.172581 s, M=130,494,464 bytes, S=708, D=1, K=19.806500, points=64.840387.


## Official board results — raw feed observed 2026-10-31 01:14:45 UTC

Watcher healthy at `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`, queue idle; all five gates passed, failure null.

- **BEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.
- **LATEST:** `run-0a911c17bddb`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.167621 s, M=136,581,120 bytes, S=708, D=1, K=19.914999, points=64.959015.


## Official latest board results — raw feed observed 2026-10-31 01:19:37 UTC

Watcher healthy at `266578e73fec11894c067b8b11a0910657a8ccff`, queue idle; all five gates passed for all four tracks, failure null.

- **BEST:** `run-e6aa2c1e3d1d`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.163797 s, M=129,777,664 bytes, S=708, D=1, K=20.353058, points=65.431484.
- **LATEST:** `run-03fcb22b8442`, commit `266578e73fec11894c067b8b11a0910657a8ccff`; T=0.172741 s, M=132,890,624 bytes, S=708, D=1, K=19.725411, points=64.751303.


## Frontier D bucketed-queue challenger — official BEST

- Source from `sd-td/frontier/d-claude-architecture-2`, branch head `92c5befeeb97aae41a02445760038edcd56a5f8e`, solver blob `d9de7159f8b34e4a20f95d06410780bf65626acf`; official Dockerfile/manifest retained, D=1. Parent rollback source is in commit `5a58796`.
- CI run [41154607933](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41154607933), source head `399c1560dcaa7f2174777f58aff45d2357e0a58a`, passed random/adversarial differential checks, official generated cases and full seed-1 hashes, and pinned official-style Docker/output comparison. The latest branch head adds only benchmark/test documentation beyond that tested solver.
- Paired local full-seed-1 median T=0.28 s vs 0.33 s; fresh-cgroup peak M=90 MB vs 105–125 MB at 12 threads, THP=always; exact output SHA on every pass. These are runner-local matched measurements, not board axes.
- **Official board:** `run-8a414d83e226` on commit `09ee42d8656b9b599401140eb38d5d76b07a7566` scored T=0.133086 s, M=98,922,496 bytes, S=727, D=1, K=23.745005, points=68.778613. New BEST; all five gates passed. Versus previous BEST `run-e6aa2c1e3d1d`, T fell 18.7%, M fell 23.8%, and S rose 19 lines. This confirms and exceeds the prior estimated K range; it is the measured result.


## Official board results — raw feed observed 2026-10-31 01:25:23 UTC

Watcher healthy at `09ee42d8656b9b599401140eb38d5d76b07a7566`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-8a414d83e226`, commit `09ee42d8656b9b599401140eb38d5d76b07a7566`; T=0.133086 s, M=98,922,496 bytes, S=727, D=1, K=23.745005, points=68.778613.
- **LATEST:** `run-8a414d83e226`, commit `09ee42d8656b9b599401140eb38d5d76b07a7566`; T=0.133086 s, M=98,922,496 bytes, S=727, D=1, K=23.745005, points=68.778613.
