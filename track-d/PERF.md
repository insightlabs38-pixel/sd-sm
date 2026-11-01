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


## D frontier PR #2 memory-release follow-up — official BEST

Latest PR head `f726b0da448c469ee2625125d29e7c12824d04db` changes only `g.perm.release()` after query translation; source blob `8da532c2b6c4ab112eb7e795b2d827728498ba60`. CI [41154994513](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41154994513) passed random/adversarial differential, official generated/full seed-1 outputs, and pinned Docker sample/full byte comparison. This frees graph permutation storage before solving queries. The original frontier source scored K=23.745005 on `run-8a414d83e226`; memory-release follow-up scored K=23.812720 on `run-d3f15b874887`, then K=23.855961 on the exact same source in `run-1cbdf9e4a82e`.


## Official board results — raw feed observed 2026-10-31 01:31:36 UTC

Watcher healthy at `ed14252dd1ed2a882887dffd6bb61950f03a1c85`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-d3f15b874887`, commit `ed14252dd1ed2a882887dffd6bb61950f03a1c85`; T=0.132280 s, M=98,914,304 bytes, S=728, D=1, K=23.812720, points=68.840450.
- **LATEST:** `run-d3f15b874887`, commit `ed14252dd1ed2a882887dffd6bb61950f03a1c85`; T=0.132280 s, M=98,914,304 bytes, S=728, D=1, K=23.812720, points=68.840450.


## Official board results — raw feed observed 2026-10-31 01:36:50 UTC

Watcher healthy at `03742f51c5f91e7313584860fb6de63ad83fbae4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-1cbdf9e4a82e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845.
- **LATEST:** `run-1cbdf9e4a82e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845.


## Official board latest snapshot — raw feed observed 2026-10-31 01:42:00 UTC

Watcher healthy at `3077ed42f746f6ed84d122899e611b5af3dac0e4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-1cbdf9e4a82e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845.
- **LATEST:** `run-9f9fbcb143f9`, commit `3077ed42f746f6ed84d122899e611b5af3dac0e4`; T=0.134513 s, M=98,709,504 bytes, S=728, D=1, K=23.624031, points=68.667700.

## Official board results — raw feed observed 2026-10-31 01:50:28 UTC

Watcher healthy at `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`, queue idle. All five gates passed for all four tracks; failures were null.

- **BEST:** `run-1cbdf9e4a82e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845.
- **LATEST:** `run-0bb1c789d93c`, commit `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`; T=0.132233 s, M=99,102,720 bytes, S=728, D=1, K=23.807888, points=68.836044.

## Official rollback snapshot — raw feed 2026-10-31 01:55 UTC

`run-f9d9a837e3d6` scored commit `4567e5529f0418efdd26c132701f1bf296bcb49d`; all five gates passed, failure null. **LATEST:** T=0.132983 s, M=98,697,216 bytes, S=728, D=1, K=23.760134, points=68.792444. **BEST:** `run-1cbdf9e4a82e`, K=23.855961, points=68.879845.

## Official board snapshot — raw feed 2026-10-31 02:00:12 UTC

Watcher healthy at `6bf7383dc5439ccd0768435c1932c243e16c0584`, queue idle. All five gates passed, failure null. **BEST:** `run-1cbdf9e4a82e`, K=23.855961, points=68.879845. **LATEST:** `run-a99f3f4d4fc3`, T=0.135147 s, M=98,762,752 bytes, S=728, D=1, K=23.566011, points=68.614304.

## Controlled official trial: qualified frontier donation PR #3 — 2026-10-31

- Staged only `track-d/d_traverse.cpp` from `sd-td` branch `frontier/d-claude-architecture-3`, head `93393b485782ca0edcf4e5e9ffa21b9deb7283ca`, source blob `4a249d728c074febe26502db752e1c97c5d1a279`. Existing Dockerfile and manifest are retained. Official rollback is parent commit `0629dacf5c60ddc1e986c185b9bf45b64d6fd105`, with source blob `8da532c2b6c4ab112eb7e795b2d827728498ba60` and BEST run `run-1cbdf9e4a82e` (K=23.855961).
- Developer qualification [CI 41156592344](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41156592344) passed differential, stress, sanitizer, official output-hash, and pinned-container checks at 1/4/12 workers. The branch records matched local timing and memory as exploratory evidence; the expected scoring-box effect is near break-even, so this push is a controlled submission-machine trial, not a claimed improvement.
- Official board run ID and axes: pending. Do not treat the prior D BEST as a score for this candidate.


## Donation renumbering trial — rejected and rolled back (2026-10-31)

- Official LATEST trial `run-03c554a03f7a` on commit `062d7e54614520ed5991920db8bd63579998b663` passed all five gates but measured T=0.148357 s, M=98,512,896 bytes, S=779, D=1, K=22.276367, points=67.392218. The then-current official BEST `run-1cbdf9e4a82e` on commit `03742f51c5f91e7313584860fb6de63ad83fbae4` was T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845. The trial's K was 6.6% lower, so it is not promoted.
- Restored the known-good source blob `8da532c2b6c4ab112eb7e795b2d827728498ba60` from official rollback commit `0629dacf5c60ddc1e986c185b9bf45b64d6fd105`. The rejected trial remains recoverable in commit `062d7e54614520ed5991920db8bd63579998b663` and developer PR #3; no PR #3 merge.


### Official board after Track D rollback — 2026-10-31 02:34 UTC

- On commit `8d5bc54c93a054ba70e651a7d9b802fcf9140276`, restored source blob `8da532c2b6c4ab112eb7e795b2d827728498ba60` passed all five gates. LATEST `run-95b70496a260`: T=0.145355 s, M=98,803,712 bytes, S=728, D=1, K=22.721567, points=67.821914. BEST remains `run-1cbdf9e4a82e`: T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845.
- This is the same source as BEST; LATEST is 4.8% lower K, with no source or dependency change. Keep BEST and LATEST separate and retain the rollback champion.


## Official board results — raw feed observed 2026-10-31 03:05:10 UTC

The watcher was healthy at commit `b453c295cdbca2e3c740d71d6c35e57b8dec3662`. Run `run-7c68bd0fe260` on this commit passed build, check, correctness, timeout and sandbox gates. LATEST: T=0.132803 s, M=98,938,880 bytes, S=728, D=1, K=23.764604, points=68.796529. BEST remains `run-1cbdf9e4a82e`: T=0.132055 s, M=98,439,168 bytes, S=728, D=1, K=23.855961, points=68.879845. This run did not replace BEST; retain the current source and track rollback history.


## Board baseline before multi-track trial — raw S3 feed 2026-10-31 03:49:18 UTC

- **BEST:** `run-1cbdf9e4a82e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.132055 s, M=98,439,168 B, S=728, D=1, K=23.855961, points=68.879845.
- **LATEST:** `run-25ef61c7d0e6`, official HEAD `a30276e460e00aa279aa41cca913a10a90a1a6a8`; T=0.142934 s, M=98,377,728 B, S=728, D=1, K=22.932996, points=68.023039. All five gates passed.

## D PR #4 contraction board trial — promoted

- Official run `run-68c15954870c` on submission commit `f91d9c075066881eb480cd7d27a9f33bfdc43350` passed all five gates. T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- Against prior BEST `run-1cbdf9e4a82e` (T=0.132055 s, M=98,439,168 B, S=728, K=23.855961), K improved 1.29%, T improved 7.38%, and M was effectively flat. PR #4 was merged to development main as `708739017c667e52c7ab69a0244edd9c3f875bee`; official parent `a30276e` retains the rollback source.
- The current public S3 board feed does not retain the older PR #3 trial in its BEST/LATEST records or 50-event tape, so its historical run remains unverified from that feed.


## Official baseline before Track B trial — raw feed 2026-10-31 04:14 UTC

On official HEAD `ec1140f4d0bd607a02b9fae4be61ce5fe3bae986`, LATEST `run-8c6b68249ccd` passed all five gates: T=0.123800 s, M=98,553,856 B, S=862, D=1, K=24.016322, points=69.025325. BEST remains `run-68c15954870c` on `f91d9c0`: T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.


## Official board results after Track B trial — raw feed 2026-10-31 04:17:53 UTC

HighVelocity watcher healthy at `a2f99921eaf302381af4fa63e6b131588c3fb572`; `run-73eb056e20f9` passed all five gates. **LATEST:** T=0.143326 s, M=96,808,960 B, S=862, D=1, K=22.400408, points=67.512797. **BEST:** `run-68c15954870c`, K=24.163880, points=69.158334.


## Official board snapshot — 2026-10-31 04:21:29 UTC

HighVelocity (`highvelocity-7f330e`) watcher was healthy at official HEAD `a62ff8d662a8f342256a53b20e05a3e2a9af6231`; queue clear. All five gates passed.

- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-a82509b051ec`; T=0.126333 s, M=98,807,808 B, S=862, D=1, K=23.762103, points=68.794244.


## Controlled size-only trial prepared — 2026-10-31

- Candidate imported from `sd-td` PR #5 head `94286d5ce85421fa082de37c92e4b3cf4f2e34df`; exact source blob `fd1db93b387442b018e9c368db6a5c46d6d89844`. The official contraction source and rollback remain in parent commit `498f27fb07731088b3746ed823d5c123bcc816ff`.
- CI [41168086045](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41168086045) passed seed-1 byte identity at 1/4/12 threads, 83 differential and 60 stress cases, ASan/UBSan, TSan, and pinned Docker. Fifteen interleaved full runs tied at 0.240 vs 0.243 s; 12-thread cgroup peak 74.83 vs 74.74 MB. The source removes 44 formatted lines (855 to 811); estimated +0.8% K is size-based only.
- Official board result pending; do not merge PR #5 or claim a score until every gate passes and D beats BEST.


## Official board snapshot and failed size-only experiment — 2026-10-31 04:25:59 UTC

- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-cea701502906` on `6ce631e9aed748609f3fbd289ec599cb4abf152d`; all five gates passed. T=0.126211 s, M=98,902,016 B, S=818, D=1, K=23.956590, points=68.971250. Despite 44 fewer formatted lines, K fell 0.86% vs BEST; runtime rose 3.19% and memory was nearly flat.
- Rejected PR #5 size-only candidate and restored the known-good contraction source from parent `498f27fb07731088b3746ed823d5c123bcc816ff`. PR #5 remains open and unmerged; source rollback is included in the next official checkpoint.


## Official board snapshot — 2026-10-31 04:30:35 UTC

- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-d22f396a7294` on `952084e36d4a8309c21c175f7208a40fe40c2702`; T=0.123844 s, M=98,922,496 B, S=862, D=1, K=23.994132, points=69.005252. All five gates passed.


## Official board snapshot — 2026-10-31 06:18:39 UTC

- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-a296f17e6f98` on `bd1e696b8a738a9f6d52c2faa16d9a6244c64d5e`; all five gates passed. T=0.129680 s, M=98,041,856 B, S=862, D=1, K=23.489985, points=68.544137.


## Official board snapshot — 2026-10-31 06:23:31 UTC

- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-ebbe2e23b0e6` on `8e70985f8a07fc6b5adaa9435c4d6b83638a2665`; all five gates passed. T=0.138829 s, M=98,529,280 B, S=862, D=1, K=22.680278, points=67.782419.

## Official board receipt — 2026-10-31 06:59:47 UTC

- Run `run-e347940b7bac` scored commit `f3bd76617870c71c81594817b54ad366113718bc`; all five gates passed. LATEST: T=0.123320 s, M=98,865,152 B, S=862, D=1, K=24.047843, points=69.053807. BEST remains `run-68c15954870c`: K=24.163880. This receipt is 0.480% below BEST; no Track D source change was included.

## Official board snapshot — 2026-10-31 07:06:34 UTC

- `run-7fee2cd3417d` scored `281c60f59cbe6c6a8c51f77aba7daad102151abd`; all five gates passed. LATEST: T=0.132595 s, M=99,069,952 B, S=862, D=1, K=23.181929. BEST remains `run-68c15954870c` (K=24.163880); no D source change was present in that snapshot.

## Official board snapshot — 2026-10-31 07:12:34 UTC

- `run-691b91d3225b` scored `aa84dc52fefa309db4dbc5c2b9aefc07863ea13a`; all five gates passed. LATEST: T=0.123910 s, M=98,648,064 B, S=862, D=1, K=24.001072. BEST remains `run-68c15954870c` (K=24.163880); no D source change was present in this snapshot.

## Official board snapshot — 2026-10-31 07:17:07 UTC

- `run-fb981cbf92cb` scored exact HEAD `15cc7c6f38a26d0f3515727d6d217ba4d95094b9`; all five gates passed. LATEST: T=0.123407 s, M=98,594,816 B, S=862, D=1, K=24.052533, points=69.058041. BEST remains `run-68c15954870c` (K=24.163880).


## Official board snapshot — 2026-10-31 12:11:52 UTC

- **BEST:** `run-68c15954870c`, T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-350691c56e3c` on `2b5afc9408dcd202ca3f113e100d02fc673d04ee`; all five gates passed. T=0.125848 s, M=99,028,992 B, S=862, D=1, K=23.797203, points=68.826295.
- Track D source was not changed in this candidate trial. The current official source remains the known-good rollback candidate while its newer development-main composition awaits an exact-source qualification.


## Official candidate result — 2026-10-31 12:15:45 UTC

- Track D source was unchanged in commit `187269a`. Board run `run-1b1341c90c11` passed all five gates: T=0.132667 s, M=99,127,296 B, S=862, D=1, K=23.172956, points=68.249072. BEST remains `run-68c15954870c`, K=24.163880.
- Historical PR #3 donation trial source `4a249d728c074febe26502db752e1c97c5d1a279` scored as `run-03c554a03f7a` on commit `062d7e5`: T=0.148357 s, M=98,512,896 B, S=779, D=1, K=22.276367. It was 6.6% below then-BEST K=23.855961 and was rolled back; PR #3 is not promoted or merged.


## Staged Track D source trial — 2026-10-31

- Candidate source blob `2a7f4af8b6005b717f067d79be75a406a037d1a9` from `sd-td/main` HEAD `a78664ef5d8ce7b3986f54328430df793664d697`. It combines the developer's separately qualified four-worker graph-construction cap and exact-key bucket width 128. Their isolated pinned-Docker/full-output A/B runs are recorded above; their runner estimates are not official scores.
- The combined exact source compiled with the official submission Dockerfile's GCC flags and passed 88 differential fixtures across 1/4/12 workers and six probe limits. Full-seed and official-board gates remain pending on this exact combined source. The parent commit preserves official BEST source `be15ac2e635af157cc8db71d2df5e218d0a78446` for rollback.


## Combined-main official trial — rejected, 2026-10-31

- Run `run-351558723173` scored `ca8f1811fcefc6fdb6cc5678754f7387791f5f31`; all five gates passed. Candidate LATEST: T=0.180488 s, M=77,778,944 B, S=823, D=1, K=21.000086, points=66.111054. BEST remains `run-68c15954870c`, K=24.163880. Despite 21.0% lower memory and 4.5% fewer source lines than BEST, T rose 47.6% and K fell 13.09%; reject the combined main candidate and restore source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` from parent `2b5afc9`. The trial source remains recoverable in `ca8f181`.

## Official latest — 2026-10-31 12:21:24 UTC

- **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-351558723173`, T=0.180488 s, M=77,778,944 B, S=823, D=1, K=21.000086; all gates passed. Known-good source is restored pending rescore.


## D PR #5 size-only candidate trial — pending official board

- Staged exact open-PR source blob `fd1db93b387442b018e9c368db6a5c46d6d89844` from head `94286d5ce85421fa082de37c92e4b3cf4f2e34df`; this simplifies the known-good contraction implementation without an algorithm change. CI `41168086045` passed 83 differential fixtures, official full/sample/tiny output hashes and Docker at 1/4/12 threads. Exact source also compiled with the official submission Docker flags and passed 88 local differential cases.
- Developer's 15-round matched run was a timing tie (0.240 vs 0.243 s); 12-thread peak memory 74.83 vs 74.74 MB. Counted source fell 855 to 811 lines, so the expected gain is primarily the source-size axis and remains a board trial, not a promotion claim. Parent `e210b5d` restores the `be15ac2` official BEST source. PR #5 remains open pending official scoring; merge it only if promoted.


## D PR #5 official trial — rejected, 2026-10-31

- Run `run-5db5dc852fda` scored `f3b24e34ddb937f3bca3317cfd5d79bf021509fa`; all five gates passed. Candidate LATEST: T=0.125386 s, M=99,057,664 B, S=818, D=1, K=24.027716, points=69.035625. BEST remains `run-68c15954870c` (K=24.163880). The 44-line source reduction did not offset 2.5% higher T and 0.56% higher M; K was 0.56% below BEST. Restore source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` from parent `e210b5d`; PR #5 is not promoted and remains unmerged.

## Official latest — 2026-10-31 12:26:53 UTC

- **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-5db5dc852fda`, T=0.125386 s, M=99,057,664 B, S=818, D=1, K=24.027716; all gates passed. Known-good source is restored pending rescore.


## Official latest — 2026-10-31 12:33:30 UTC

- BEST remains `run-68c15954870c`, K=24.163880. LATEST `run-d79669d7bdb8` on `f477933130ce23aa311f60d3486480ab5de6fff8` passed all five gates: T=0.123726 s, M=99,115,008 B, S=862, D=1, K=23.996238, points=69.007158. Source is unchanged known-good blob `be15ac2e635af157cc8db71d2df5e218d0a78446`; the 0.69% gap is run variation.


## Official latest — 2026-10-31 12:40:45 UTC

- **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-7a56c38522db` on `0923ede528139a79896a6bfe1bb67934f74c5951`, all five gates passed: T=0.131600 s, M=98,553,856 B, S=862, D=1, K=23.293721, points=68.361943. Same promoted source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`; 3.60% below BEST.

## Official same-source rerun — 2026-10-31 13:17 UTC

- Run `run-0dee7b5147ee` on `b0e30144ba58e2c3b3c86c8b1fd26dffa1e655b5` passed all five gates: T=0.131610 s, M=98,836,480 B, S=862, D=1, K=23.279499. BEST remains `run-68c15954870c` (K=24.163880). Source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` is unchanged; this repeat does not change promotion.


## Official latest — 2026-10-31 13:23:53 UTC

- BEST remains `run-68c15954870c`, K=24.163880. LATEST `run-35679acda755` on `f1bcd2033e061028929c445c964768331d1a6f5e` passed all five gates: T=0.178794 s, M=98,877,440 B, S=862, D=1, K=19.971267, points=65.020281. Source remained the known-good blob `be15ac2e635af157cc8db71d2df5e218d0a78446`; this is a same-source low outlier versus `run-0dee7b5147ee` (K=23.279499), not evidence of a code regression.


## Official latest — 2026-10-31 14:17 UTC

- BEST remains `run-68c15954870c`, K=24.163880. LATEST `run-4ae6212ad26a` on `af33cf8053e100e92405aabcfa50d0278203daa1` passed all five gates: T=0.164637 s, M=98,861,056 B, S=862, D=1, K=20.812908, points=65.916638. D source `be15ac2e635af157cc8db71d2df5e218d0a78446` was unchanged; this is a low same-source result versus `run-0dee7b5147ee` (K=23.279499), not a candidate change.


## Official latest — 2026-10-31 14:22 UTC

- BEST remains `run-68c15954870c`, K=24.163880. LATEST `run-2c8d4087957b` on `e5e94a469faec38eaaf180210e468ac3060b3023` passed all five gates: T=0.130852 s, M=98,529,280 B, S=862, D=1, K=23.361369, points=68.424915. Source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` was unchanged.

## Official latest — 2026-10-31 15:12 UTC

- LATEST `run-1538c1476074` on `1657706f033d676bb97f0df87e3386978b694387` passed all five gates: T=0.129054 s, M=98,549,760 B, S=862, D=1, K=23.522566, points=68.574234. BEST remains `run-68c15954870c`, K=24.163880. Track D source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` was unchanged.

## Official latest — 2026-10-31 15:21 UTC

- LATEST `run-b8b15b4f8a36` on `480a8e3def26af26e10298d6b043bf2195c82ec3` passed all five gates: T=0.125451 s, M=96,890,880 B, S=862, D=1, K=23.939104, points=68.955395. BEST remains `run-68c15954870c`, K=24.163880. The scored D source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` was unchanged.

## Contraction-champion size refactor — official trial staged, 2026-10-31

- Candidate from open `sd-td` PR #5, commit `94286d5ce85421fa082de37c92e4b3cf4f2e34df`, source blob `fd1db93b387442b018e9c368db6a5c46d6d89844`. Its PR base source blob is exactly the scored official champion `be15ac2e635af157cc8db71d2df5e218d0a78446`; it removes repeated packing/claims code without changing the graph algorithm.
- Exact-source CI `41168086045` passed official full seed-1 hashes at 1/4/12 threads, 83 differential and 60 stress fixtures under native, ASan/UBSan and TSan, plus pinned offline Docker. The report gives interleaved medians 0.240/0.243 s (treated as a tie), peaks 74.83/74.74 MB, and source 855→811 formatted lines; expected K gain is about 0.8% from S only.
- Official trial pending. Parent `480a8e3def26af26e10298d6b043bf2195c82ec3` preserves rollback to the scored champion. This is not yet a promoted PR.

## Official refactor trial rejected — 2026-10-31 16:13 UTC

- D trial `run-71949d2f6d95` on `8298e2cbe0d21ffd4688bb23b625f988fdd4128d` passed all five gates, but scored T=0.159076 s, M=98,557,952 B, S=818, D=1, K=21.353741, points=66.473698. Prior same-source LATEST on champion blob `be15ac2e635af157cc8db71d2df5e218d0a78446` was `run-b8b15b4f8a36`: T=0.125451 s, M=96,890,880 B, S=862, K=23.939104; BEST remains `run-68c15954870c`, K=24.163880. The 44-line reduction did not offset the measured runtime and memory regression.
- Reject PR #5 candidate blob `fd1db93b387442b018e9c368db6a5c46d6d89844`; restore champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` from parent `480a8e3def26af26e10298d6b043bf2195c82ec3`. Candidate remains recoverable in commit `8298e2cbe0d21ffd4688bb23b625f988fdd4128d`.


## Official latest — 2026-10-31 16:19 UTC

- LATEST `run-9583089ac011` on submission `d4b9c4d51f4d0c3fc2d58a1fc9bf6c66ef642ed9` passed all five board gates: T=0.133682 s, M=98,525,184 B, S=862, D=1, K=23.112963, points=68.192781. BEST remains `run-68c15954870c`, K=24.163880; champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` unchanged.


## Official latest — 2026-10-31 16:27 UTC

- LATEST `run-82e000147b19` on `70d512481b36d111e017909f4b76e257f69db9ea` passed all five gates: T=0.129004 s, M=98,615,296 B, S=862, D=1, K=23.523996, points=68.575555. BEST remains `run-68c15954870c`, K=24.163880; champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` unchanged.

## Official latest — 2026-10-31 16:33 UTC

- LATEST `run-50da3a129596` on official commit `0ef3758e08e015c6f1ba97b9d36966ec151efc40` passed all five board gates: T=0.133828 s, M=98,947,072 B, S=862, D=1, K=23.080619, points=68.162373. BEST remains `run-68c15954870c`, K=24.163880; champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` unchanged.


## Full-team board results — 2026-10-31 16:39–16:45 UTC

All five gates passed. Track D champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` was unchanged across these runs.

- **BEST:** `run-68c15954870c`, T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-680e60b4d195` on official commit `242c9bf8b5169359fbe30b30245cf799f1662304`: T=0.146857 s, M=98,844,672 B, S=862, D=1, K=22.037563, points=67.158178.
- Previous receipts: `run-aa83d758d6fd` on `92c095f030bd9519de41ab7201a944cc9d94cbd6`: T=0.127111 s, M=98,549,760 B, S=862, K=23.701665; `run-50da3a129596` on `0ef3758e08e015c6f1ba97b9d36966ec151efc40`: K=23.080619.
- The lower latest score is measurement variability; D source was unchanged. No D candidate was promoted.


## Full-team board run — 2026-10-31 16:49 UTC

All five gates passed on official commit `6a01ff11b17d179835197e73cbab6518a6651b79` with the unchanged champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`.

- **LATEST:** `run-4468cb61df96`: T=0.134813 s, M=98,869,248 B, S=862, D=1, K=22.999765, points=68.086170.
- **BEST** remains `run-68c15954870c`, K=24.163880. No D source candidate was promoted.

## LIFO frontier layout — qualified but rejected by developer tournament

The D developer's current main HEAD `9eb8be46ba369057e9ece3e3d3c275821ece0552` records the exact LIFO-vs-FIFO test. Workflow [41221039514](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41221039514) passed 88 differential fixtures, exact tiny/sample/full outputs, Docker at 1/4/12 workers, and 78 additional exact full runs. In 13 matched pairs, LIFO had 0/13 wins at four workers, 1/13 at six, and 0/13 at twelve; median wall time and user CPU were higher while RSS stayed about 69.3 MiB. Keep the existing FIFO/BFS layout; candidate branch `d/lifo-frontier-layout-20261031` is not promoted. The first workflow run failed only in RSS parsing; the corrected run passed.


## Full-team board run — 2026-10-31 16:54 UTC

All five gates passed on official commit `77a70106fecd5098a0a152a47f8e7383a3c1e9c5` with the unchanged FIFO/BFS champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** `run-15dd0ef8e018`, T=0.128927 s, M=99,205,120 B, S=862, D=1, K=23.502972, points=68.556139. BEST remains `run-68c15954870c`, K=24.163880. No D source promotion.


## Latest board result — 2026-10-31 17:00 UTC

All five gates passed on commit `74a4fb7456ce5fb8b10ef5b0eeef2d58289fdc59` with the unchanged FIFO/BFS champion blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** `run-fae2a1d3c886`, T=0.131225 s, M=98,959,360 B, S=862, D=1, K=23.307832, points=68.375094. BEST remains `run-68c15954870c`, K=24.163880.


## Full-team board run — 2026-10-31 17:05 UTC

All five gates passed on commit `23be16823a7232064b3090b805ff80b6c086cfa9` with the unchanged FIFO/BFS champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** `run-0e0e12c32dce`, T=0.129998 s, M=98,738,176 B, S=862, D=1, K=23.428052, points=68.486809. BEST remains `run-68c15954870c`, K=24.163880.


## Full-team board result — 2026-10-31 17:10 UTC

All five gates passed on official commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818` with FIFO/BFS champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** `run-8a6d8f42e333`, T=0.136779 s, M=98,725,888 B, S=862, D=1, K=22.840500, points=67.935281. BEST remains `run-68c15954870c`, K=24.163880.


## Full-team board result — 2026-10-31 17:19 UTC

All five gates passed on official commit `c4cb49fedd910dd65dc0719c113b06fa2e9c2476` with the unchanged FIFO/BFS source. **LATEST:** `run-9e66d213af2e`, T=0.140122 s, M=98,873,344 B, S=862, D=1, K=22.559659, points=67.666626. BEST remains `run-68c15954870c`, K=24.163880.


## Latest board result — 2026-10-31 17:30 UTC

All five gates passed on `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122` with the unchanged FIFO/BFS source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** `run-4a56fed6018e`, T=0.136810 s, M=98,713,088 B, S=862, D=1, K=22.815428, points=67.911431. BEST remains `run-68c15954870c`, K=24.163880.

## Adjacency-order tournament — qualified but not promoted

D main HEAD `c844d839fc98efec7029e952c65ae81b6cd8d704` records CI [41225764825](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41225764825): exact-output and Docker gates passed, with 195 full-seed executions. Reversed-order variants had weak, inconsistent wins at 4/6 workers and lost more often at 12; RSS was unchanged. Retain original adjacency order; no D source trial warranted.


## Official board results — raw feed, 2026-10-31 18:17 UTC

All five gates passed on official commit `a91a77e9ad3a54d93385b3bfc5231da589395f1c`.
- **BEST:** `run-68c15954870c`; T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880, points=69.158334.
- **LATEST:** `run-eaacbe3f05c5`; T=0.123623 s, M=98,160,640 B, S=862, D=1, K=24.052733, points=69.058221.
- Latest uses the same D source but is below BEST on K; no promotion warranted.


## Official latest — run-c75b6d7b493b (2026-10-31 18:25 UTC)

All five gates passed on commit `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`. **LATEST:** T=0.144120 s, M=98,668,544 B, S=862, D=1, K=22.253774, points=67.370183. **BEST** remains `run-68c15954870c` (T=0.122315 s, M=98,508,800 B, S=862, D=1, K=24.163880). Source is unchanged; retain champion.


## Track D size-efficiency trial staged — 2026-10-31

- Candidate from open `sd-td` PR #5, head `94286d5ce85421fa082de37c92e4b3cf4f2e34df`, source blob `fd1db93b387442b018e9c368db6a5c46d6d89844`; it is a size-only simplification of the known champion, with 855→811 formatted lines.
- CI [41168086045](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41168086045) passed full seed-1 byte equality at 1/4/12 threads, 83 differential and 60 stress cases, ASan/UBSan, and TSan. Developer 15-round medians were 0.243→0.240 s (tie); 12-thread peak cgroup memory was 74.74→74.83 MB. Expected K gain is about 0.8% from source size; official scoring is pending.
- Rollback champion source remains `be15ac2e635af157cc8db71d2df5e218d0a78446` in parent `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`. PR #5 remains open until official gates and measured K justify promotion.


## Official PR #5 trial and rollback — run-fa80a2e1686e (2026-10-31 18:31 UTC)

- All five gates passed for candidate blob `fd1db93b387442b018e9c368db6a5c46d6d89844`, but its **LATEST** score was T=0.142037 s, M=98,885,632 B, S=818, D=1, K=22.583292, points=67.689362. This is below the champion BEST `run-68c15954870c` (K=24.163880); source-size savings did not offset measured T/M.
- Restored champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` from parent `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`. PR #5 remains open and unmerged; candidate source is retained in official commit `5b1f942cac523c62dcda40eca63586732c6a7959`.


## Official latest after champion rollback — run-bc7637ed7a02 (2026-10-31 18:37 UTC)

All five gates passed. **LATEST:** T=0.124132 s, M=98,762,752 B, S=862, D=1, K=23.974029, points=68.987051. **BEST** remains `run-68c15954870c` (K=24.163880); the D PR #5 source-size trial is rejected for promotion and stays in history at `5b1f942`.


## Official latest — run-9d862fe07f96 (2026-10-31 18:50 UTC)

All five gates passed on the restored champion. **LATEST:** T=0.126545 s, M=98,881,536 B, S=862, D=1, K=23.738649, points=68.772800. **BEST** remains `run-68c15954870c` (K=24.163880).


## Official latest — run-2f74e4744b5b (2026-10-31 18:56 UTC)

All five gates passed. **LATEST:** T=0.133651 s, M=98,807,808 B, S=862, D=1, K=23.102404, points=68.182859. **BEST** remains `run-68c15954870c` (K=24.163880).


## Official latest — run-ffd3342069fb (2026-10-31 19:02 UTC)

All five gates passed on the champion source. **LATEST:** T=0.129919 s, M=98,672,640 B, S=862, D=1, K=23.438286, points=68.496293. **BEST** remains `run-68c15954870c` (K=24.163880).


## Official latest — run-016d47de2a5e (2026-10-31 19:08 UTC)

All five gates passed on the then-current champion source. **LATEST:** T=0.131148 s, M=99,233,792 B, S=862, D=1, K=23.301763, points=68.369439. **BEST** remains `run-68c15954870c` (K=24.163880).

## Candidate submitted for official evaluation

This commit replaces D with developer main blob `d53a4e39a379c744724d4aac87b6a3925411d9cf` (671 lines, 29,391 bytes; champion was 693 lines, 30,661 bytes). Developer verification reports 88 differential cases, tiny/sample/full hash checks, holdout seeds, and pinned offline Docker passing. Matched 31-pair four-vCPU medians improved 0.250009→0.249562 s, 6-worker 0.252153→0.249022 s, and 12-worker 0.258902→0.255439 s; those are proxy measurements, not board scores. **BEST remains `run-68c15954870c`** pending this official run.


## Official candidate result — run-066fcc7e1635 (2026-10-31 19:16 UTC)

All five gates passed on developer-main source blob `d53a4e39a379c744724d4aac87b6a3925411d9cf`. T=0.173784 s, M=77,803,520 B, S=825, D=1, K=21.392168, points=66.512740. Despite lower memory and smaller source, K is well below **BEST** `run-68c15954870c` (K=24.163880); reject promotion and restore champion blob `be15ac2e635af157cc8db71d2df5e218d0a78446` after dispatch cooldown. Candidate remains reachable in the preceding integration commit for rollback/audit.


## Official latest — run-a7bcabdc0bdf (2026-10-31 19:24 UTC)

All five gates passed on restored champion blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. **LATEST:** T=0.140765 s, M=99,217,408 B, S=862, D=1, K=22.492443, points=67.601831. **BEST** remains `run-68c15954870c` (K=24.163880).


## Official latest — run-91691d63184a (2026-10-31 19:29 UTC)

All five gates passed on restored champion source. **LATEST:** T=0.125720 s, M=98,537,472 B, S=862, D=1, K=23.833019, points=68.858953. **BEST** remains `run-68c15954870c` (K=24.163880).


## Official latest — run-ad74c5d9cf1a (2026-10-31 19:42 UTC)

All five gates passed on restored champion source. **LATEST:** T=0.136574 s, M=98,439,168 B, S=862, D=1, K=22.870936, points=67.964197. **BEST** remains `run-68c15954870c` (K=24.163880).

## Official board run — 2026-10-31 19:46 UTC

Run `run-ad74c5d9cf1a` scored commit `2602c63339f532be813056b0c05bb573835f6766`; all five gates passed, failure null. **LATEST:** T=0.124611 s, M=98,451,456 bytes, S=862, D=1, K=23.943019. **BEST** remains `run-68c15954870c`, K=24.163880.

## Official board result — commit 3384246, dispatch 2026-10-31 19:52 UTC

Run `run-6e9ec3791593`; all five gates passed. T=0.133873 s, M=98,717,696 bytes, S=862, D=1, K=23.087454, points=68.168802. **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-6e9ec3791593`.

## Official board result — commit 13b8fec, dispatch 2026-10-31 19:57 UTC

Run `run-37fdcc496c04`; all five gates passed. T=0.152867 s, M=99,086,336 bytes, S=862, D=1, K=21.589467, points=66.712096. **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-37fdcc496c04`. Next official frontier trial is D PR #5, source blob `fd1db93b387442b018e9c368db6a5c46d6d89844`; exact-head CI passed byte-equality at 1/4/12 threads, 83 differential and 60 stress cases, ASan/UBSan and TSan. Fifteen interleaved rounds measured 0.240 vs 0.243 s (tie) and 74.83 vs 74.74 MB; the expected gain is source-size reduction, about +0.8% K.

## Official board result — commit 555cd61, dispatch 2026-10-31 20:03 UTC

Run `run-8af02b0a1b7b`; all five gates passed. T=0.129822 s, M=98,594,816 bytes, S=818, D=1, K=23.635765, points=68.678483. **BEST:** `run-68c15954870c`, K=24.163880. **LATEST:** `run-8af02b0a1b7b`; D PR #5's size-only refactor did not beat BEST. Next D frontier trial is PR #3, source blob `4a249d728c074febe26502db752e1c97c5d1a279`; exact source matches successful CI `41156592344` and pinned Docker passed across 1/4/12 workers. Local 4-core speed was 0.265→0.259 s, 12-thread peak memory stayed about 81 MB; its +51 formatted lines and modest expected gain must still win complete official K.


## Official board result — trial commit 9743d05 (2026-10-31 20:09:57 UTC)

Run `run-f3a17140e30a`; all five gates passed on D PR #3 head source. T=0.166259 s, M=98,877,440 B, S=779, D=1, K=21.027371, points=66.139249. This is below qualified BEST `run-68c15954870c` (K=24.163880); **LATEST** is the rejected PR #3 trial. Restore the known-good D source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`; leave PR #3 open and unmerged.


## Official board result — commit 3c9845a (2026-10-31 20:15:02 UTC)

Run `run-9dc94daabc82`; all five gates passed on the restored D champion source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. T=0.155857 s, M=99,172,352 B, S=862, D=1, K=21.377665, points=66.498013. **LATEST** remains below **BEST** `run-68c15954870c` (K=24.163880); the D PR #3 regression is retained as an informative prior trial and remains open/unmerged.


## Official board result — commit fa0f0b4 (2026-10-31 20:20:02 UTC)

Run `run-875f39c7d6bf`; all five gates passed. T=0.133503 s, M=99,045,376 B, S=862, D=1, K=23.104107, points=68.184459. **LATEST**; **BEST** remains `run-68c15954870c` at K=24.163880.


## Official board result — commit c2397c9 (2026-10-31 20:26:59 UTC)

Run `run-a6ce3d0c3345`; all five gates passed. T=0.139103 s, M=98,516,992 B, S=862, D=1, K=22.658495, points=67.761553. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — reserve-trial commit 74145b5 (2026-10-31 21:10:54 UTC)

Run `run-4ba6216ffe99`; all five gates passed on the restored D champion source. T=0.139007 s, M=98,603,008 B, S=862, D=1, K=22.662362, points=67.765258. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — champion-only commit ac7ea0e (2026-10-31 21:15:54 UTC)

Run `run-bfad9e9f55ae`; all five gates passed. T=0.135189 s, M=99,094,528 B, S=862, D=1, K=22.957306, points=68.046046. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 260134e (2026-10-31 21:23:17 UTC)

Run `run-1cb5a88793c9`; all five gates passed. T=0.163166 s, M=99,184,640 B, S=862, D=1, K=20.892856, points=65.999891. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 954e3c7 (2026-10-31 22:12:50 UTC)

Run `run-0b0237a52c1d`; all five gates passed. T=0.133224 s, M=96,333,824 B, S=862, D=1, K=23.257045, points=68.327727. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 62eaaeb (2026-10-31 23:10:08 UTC)

Run `run-5cce588761ac`; all five gates passed. T=0.128204 s, M=96,436,224 B, S=862, D=1, K=23.702967, points=68.740135. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 97ebf28 (2026-10-31 23:15:08 UTC)

Run `run-60fcb5da7515`; all five gates passed. T=0.127611 s, M=98,639,872 B, S=862, D=1, K=23.650862, points=68.692349. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit c096950 (2026-10-31 23:55:08 UTC)

Run `run-706143ab2e96`; all five gates passed. T=0.123146 s, M=98,418,688 B, S=862, D=1, K=24.086620, points=69.088793. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 7dc6a03 (2026-10-31 23:58:28 UTC)

Run `run-d97b34c70176`; all five gates passed. T=0.134295 s, M=98,975,744 B, S=862, D=1, K=23.039119, points=68.123293. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit f8cfd3d (2026-11-01 00:10:50 UTC)

Run `run-d9fa2e2a42a9`; all five gates passed. T=0.130135 s, M=98,668,544 B, S=862, D=1, K=23.419021, points=68.478437. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit eeef411 (2026-11-01 00:17:52 UTC)

Run `run-e5e30feaa742`; all five gates passed. T=0.134647 s, M=98,861,056 B, S=862, D=1, K=23.014320, points=68.099907. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).

## Official board result — commit d1cb0e5 (2026-11-01 00:22:52 UTC)

Run `run-9ca16eaf094b`; all five gates passed. T=0.123495 s, M=98,856,960 B, S=862, D=1, K=24.031197, points=69.038770. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).

## Official board result — commit cf46ad7 (2026-11-01 00:32:52 UTC)

Run `run-7bc253d5404a`; all five gates passed. T=0.123252 s, M=98,529,280 B, S=862, D=1, K=24.070853, points=69.074574. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit b665afd (2026-11-01 00:37:52 UTC)

Run `run-c4a700c109db`; all five gates passed. T=0.125372 s, M=98,639,872 B, S=862, D=1, K=23.861116, points=68.884538. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 925095f (2026-11-01 00:42:54 UTC)

Run `run-c17d46a610eb`; all five gates passed. T=0.123557 s, M=98,402,304 B, S=862, D=1, K=24.047327, points=69.053340. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 16126e3 (2026-11-01 00:47:54 UTC)

Run `run-0d16208b2f33`; all five gates passed. T=0.126902 s, M=99,139,584 B, S=862, D=1, K=23.692882, points=68.730894. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 12673d7 (2026-11-01 00:52:54 UTC)

Run `run-94a31ca966c7`; all five gates passed. T=0.123219 s, M=98,598,912 B, S=862, D=1, K=24.070675, points=69.074414. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 32bcf03 (2026-11-01 00:57:54 UTC)

Run `run-c56f751008f5`; all five gates passed. T=0.130290 s, M=99,192,832 B, S=862, D=1, K=23.380292, points=68.442497. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880). D source was unchanged.

## Current D main trial — official validation pending

Imported only source blob `e63d989d3f55eee80dbc5ffbadeed970d2977d19` from D main commit `f6597dac4591381a8be65bb3e78bf52c992ba041`: one adjacency-data prefetch following the already qualified bucket-offset prefetch. Native paired tournament CI `41257386264` (21 passes) and GCC15 PGO tournament `41257609838` (25 passes) measured baseline→candidate medians of 0.220373→0.216304 s at 4 workers (1.85%, 21/25 wins), 0.226040→0.219051 s at 6 (3.09%, 24/25), and 0.235647→0.227380 s at 12 (3.51%, 21/25). All 234 PGO full-seed runs matched the reference hash; independent qualification `41258118198` passed differential/stress, exact tiny/sample/full hashes, pinned offline PGO Docker, and full-data worker counts 1/4/6/12. These are developer PGO measurements, not official T/M/S/D/K. This official repository keeps its non-PGO Dockerfile/config; the source also compiles under its C++17 flags. **Official K pending.** Rollback source is `be15ac2e635af157cc8db71d2df5e218d0a78446` in prior checkpoint `41fb666`.

## Official board result — commit 033819b (2026-11-01 01:02:54 UTC)

Run `run-9c7910f04cb3`; all five gates passed, but cumulative D-main source regressed: T=0.170178 s, M=77,557,760 B, S=829, D=1, K=21.615620, points=66.738384. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880; T=0.122315 s, M=98,508,800 B, S=862). Rejected cumulative source `e63d989d3f55eee80dbc5ffbadeed970d2977d19`; this submission restores rollback source from `41fb666` (blob `be15ac2e635af157cc8db71d2df5e218d0a78446`). The result demonstrates the one-line prefetch benchmark against D main did not predict official score for the cumulative candidate.


## Official board result — commit 832a496 (2026-11-01 01:07:54 UTC)

Run `run-fa577b085e91`; all five gates passed on exact BEST D source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. T=0.132627 s, M=99,000,320 B, S=862, D=1, K=23.182392, points=68.257912. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880). This lower same-source result occurred alongside slower A/B/C receipts and does not displace the champion.


## Official board result — commit bc48c37 (2026-11-01 01:12:54 UTC)

Run `run-69641193c5c9`; all five gates passed on BEST D source blob `be15ac2e635af157cc8db71d2df5e218d0a78446`. T=0.127663 s, M=98,897,920 B, S=862, D=1, K=23.633693, points=68.676579. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit 62c5bf4 (2026-11-01 01:17:54 UTC)

Run `run-6bb93f355d5c`; all five gates passed on exact BEST D source `be15ac2e635af157cc8db71d2df5e218d0a78446`. T=0.126878 s, M=98,791,424 B, S=862, D=1, K=23.711800, points=68.748226. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).


## Official board result — commit d411050 (2026-11-01 01:22:54 UTC)

Run `run-d267e4388d7c`; all five gates passed on exact BEST D source `be15ac2e635af157cc8db71d2df5e218d0a78446`. T=0.134675 s, M=99,012,608 B, S=862, D=1, K=23.004879, points=68.090997. **LATEST**; **BEST** remains `run-68c15954870c` (K=24.163880).

## Frontier PR #10 submitted for official validation (2026-11-01)

Imported only `track-d/d_traverse.cpp` from open PR #10, head `0b0a71409399192ae1ff174dc6c08f36cca03a15`, exact source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. This replaces construction plus query traversal with fused degree-2 contraction/BFS/gather and branch-free bidirectional search; its pinned PGO Dockerfile is unchanged in the developer repo, and this official submission keeps its own pinned Dockerfile. Qualification `41266930539` passed, including exact official hashes, 88 differential/60 stress cases at 1/4/12 workers, 72 race-sensitive seeds and ASan/UBSan/TSan; follow-up `41267528143` passed after main merge. Developer paired medians versus exact BEST source `be15ac2e`: 4 workers 238.8→201.1 ms, 12 workers 256.5→213.8 ms; THP=always cgroup peak 80→62 MB; formatted S approximately 855→776. These are developer measurements, not official scoring-box axes. Candidate is a major architecture change and is sent for direct official validation. **T/M/S/D/K pending.** Rollback/BEST remains source blob `be15ac2e635af157cc8db71d2df5e218d0a78446` from parent `8b6f450`; merge PR #10 only if official scoring promotes it.


## Frontier PR #10 official promotion — commit 132ef00 (2026-11-01 04:06:36 UTC)

Run `run-4dbbefad4adc`; all five gates passed on source `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.111756 s, M=67,698,688 B, S=783, D=1, K=27.644700, points=72.080594. **BEST = LATEST**, +14.4% K versus former BEST `run-68c15954870c` (K=24.163880), with T -8.6%, M -31.3%, S -79. PR #10 was merged to `sd-td/main` at `307f11c640d3013aa023f26a75fe8d9f4dac8abd`; D rollback remains available in prior official commits, exact old source `be15ac2e635af157cc8db71d2df5e218d0a78446`.

## Official board result — commit 4a4461e (2026-11-01 04:11:36 UTC)

Run `run-720d92385f68`; all five gates passed on D PR #10 blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.118737 s, M=73,125,888 B, S=783, D=1, K=26.409252, points=71.087805. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700), +9.3% over the former BEST `run-68c15954870c` (K=24.163880). Retain the promoted PR #10 source; no rollback is indicated by this lower repeat.

## Official board result — commit a13b5ef (2026-11-01 04:16:46 UTC)

Run `run-8f54880b6707`; all five gates passed on D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.115853 s, M=72,269,824 B, S=783, D=1, K=26.798983, points=71.405916. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700), same source. Latest remains 10.9% above the former BEST `run-68c15954870c` (K=24.163880).
Sequential same-source comparison with `run-720d92385f68` on commit `4a4461e`: K 26.409252→26.798983 (+1.48%), T 0.118737→0.115853 s (-2.43%), M 73,125,888→72,269,824 B (-1.17%). This repeat remains below D BEST and provides a direct estimate of run-to-run variation.

## Official board result — commit 0e56118 (2026-11-01 04:23:34 UTC)

Run `run-9bd4fa3b77b8`; all five gates passed. T=0.112929 s, M=67,596,288 B, S=783, D=1, K=27.509079, points=71.973803. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700), same D PR #10 source.

## Official board result — commit f281e05 (2026-11-01 04:30:02 UTC)

Run `run-c6d4d4b15d34`; all five gates passed. T=0.114127 s, M=69,521,408 B, S=783, D=1, K=27.211059, points=71.737273. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700), same D PR #10 source.

## Official board result — commit 1633378 (2026-11-01 04:36:05 UTC)

Run `run-327baed9cf95`; all five gates passed on D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.112463 s, M=71,090,176 B, S=783, D=1, K=27.289565, points=71.799831. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). This is within 0.29% K of same-source run `run-c6d4d4b15d34`; retain BEST.

## Official board result — commit 116914f (2026-11-01 04:41:53 UTC)

Run `run-ee5a05a9a44f`; all five gates passed on unchanged D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.114332 s, M=67,805,184 B, S=783, D=1, K=27.322906, points=71.826344. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official board result — commit b5b3fec (2026-11-01 04:47:45 UTC)

Run `run-cf9be292c16b`; all five gates passed on unchanged D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.113268 s, M=78,319,616 B, S=783, D=1, K=26.670775, points=71.301782. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## D fused-probe depth 128 frontier — tested, not promoted

Branch `d/fused-owner-probe-20261101` head `54788fc7baa30f8b1baf0a2860cae60a29315eb6`, source blob `ba344a996df8b60d5aad7748a3ead12931460a92`. CI `41274089238` succeeded: 88 differential cases across worker/probe combinations and 17 interleaved full-input rounds with exact hashes at 4/6/12 workers. Default owner partition remains selected; only `SD_PROBE=128` is chosen. Against default `SD_PROBE=256`, median wall T was 0.202542→0.201805 s (4 workers, -0.36%), 0.214857→0.214096 s (6 workers, -0.35%), and 0.217176→0.214801 s (12 workers, -1.09%). These are developer runner results, not official board axes. Imported only `track-d/d_traverse.cpp` and set `-DSD_PROBE=128` in the official pinned static C++17 build. Exact official flags compiled locally. Official gates passed, but the board K result did not support promotion; PR #10 blob `b7a527b058991dce7967738d3695f8ab3917a75d` and its Dockerfile were restored in commit `ecc160b`. The candidate source remains in parent `de9c67e` for rollback/audit. No PR exists for this frontier branch.

## Official result — D fused-probe depth 128 frontier (commit de9c67e, 2026-11-01 04:53:02 UTC)

Run `run-40e0cc1582ec`; all five gates passed on source blob `ba344a996df8b60d5aad7748a3ead12931460a92` with Docker flag `-DSD_PROBE=128`. T=0.115277 s, M=73,842,688 B, S=792, D=1, K=26.704596, points=71.329301. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700) on D PR #10. Relative to baseline PR #10 run `run-cf9be292c16b`, K improved only 0.13% while T regressed 1.77%, M fell 5.72%, and S increased by 9. This mixed, near-noise result does not justify promotion; restore PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d` and its Dockerfile in the next checkpoint. CI `41274089238` and the developer 17-round results remain documented above; no PR exists for this branch.

- Official `speed-demon` commit `eeec788784e06afa814bc442630cd2d3a1d42001`: run `run-3c69d2840c0f`, all five gates passed after restoring the known-good D PR #10 source and Dockerfile (blob `b7a527b058991dce7967738d3695f8ab3917a75d`); no probe-128 variant. T=0.112446 s, M=71,737,344 B, S=783, D=1, K=27.242208, points=71.762115. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Against PR #10 run `run-cf9be292c16b`, K improves 2.14% with T down 0.73% and M down 8.39%; this is a repeat on the same source, and BEST remains unchanged.

- Repeat official run on source-identical commit `6917275dbd2ee12fd19df6fe3b87a60920c86ef8`: `run-17b95177f3ab`, all five gates passed. T=0.119562 s, M=68,587,520 B, S=783, D=1, K=26.657398, points=71.290888. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No D source change; same-source variance does not justify replacing the known-good champion.

- Repeat official run on source-identical commit `17a6d96ba2cf813bac7eea2225b51fdd4d34960a`: `run-0fa8059df956`, all five gates passed. T=0.114077 s, M=71,225,344 B, S=783, D=1, K=27.085534, points=71.636870. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No D source change.

- Official run on `0d48c0b1302610385c4608b30b6842aa71e388cb`: `run-d904da3680dd`, all five gates passed on unchanged D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.116308 s, M=76,644,352 B, S=783, D=1, K=26.433979, points=71.108127. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-e56dda8710e9` on checkpoint `b70956dd71a72aec0c5bace4f41dcf3a9807f8ba`; all five gates passed on unchanged D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.115098 s, M=67,723,264 B, S=783, D=1, K=27.238419, points=71.759095. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-3f140abb4931` on `dde14ac917c8ad8642c734162b25804a4008cc90`; all five gates passed on unchanged D PR #10 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.119360 s, M=71,426,048 B, S=783, D=1, K=26.464435, points=71.133132. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). The simultaneous source-identical K dips on A–D reinforce timing variance; do not infer regression.

## D PR #11 main promotion — official scoring-box trial pending

- Imported exact selected D main source blob `484ed6182b9d2e0e3482b6818549077f637890a5` from merged PR #11 (`cd9464c8`, merge `638b9dff`); rollback is the parent-selected source blob `b7a527b058991dce7967738d3695f8ab3917a75d`.
- The change caps graph-build workers at `min(4, query_workers)` while preserving query worker count and algorithms. The exact source passed qualification CI `41285935356` (offline pinned PGO Docker, 1/4/12 worker checks, 88 differential cases and official hashes). The developer's 255-run matched tournament found 4-build workers beat 6-build 15/17 at six query workers (0.255494 vs 0.272465 s) and 12-build 17/17 at 12 query workers (0.250649 vs 0.263268 s); local runner evidence, not official scoring evidence.
- Previous official source result `run-3f140abb4931` on blob `b7a527b0`: T=0.119360 s, M=71,426,048 B, S=783, D=1, K=26.464435. PR #11's official T/M/S/D/K and gates are pending; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-2150cb073997` on `346a17e08d7356487484b804bbd9a0a456bfa4f5` tested PR #11 blob `484ed6182b9d2e0e3482b6818549077f637890a5`; all five gates passed. T=0.154034 s, M=66,195,456 B, S=784, D=1, K=23.648646, points=68.690314. Compared with prior selected blob `b7a527b0` on `run-3f140abb4931`, T increased 29.05%, M fell 7.32%, and K fell 10.64%. **Reject PR #11 for official promotion**; restore source blob `b7a527b058991dce7967738d3695f8ab3917a75d`. **LATEST** is `run-2150cb073997`; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official rollback run `run-de48fc8596db` on `d3af7efd6ac8fd8982cbaae3b759052ccd74547f` restored prior selected source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; all five gates passed. T=0.113548 s, M=67,792,896 B, S=783, D=1, K=27.418064, points=71.901839. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). This confirms the PR #11 trial rejection/rollback.

- Official run `run-733a795908e8` on `bf2de0f901f0e5bc2e1dc07331fd0de0622ff400` verified the rollback blob `b7a527b058991dce7967738d3695f8ab3917a75d`; all five gates passed. T=0.119262 s, M=67,534,848 B, S=783, D=1, K=26.773598, points=71.385337. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-2bd0cecfd207` on `82d831033431c94a929d3c0eb99d62a0d061583a`; all five gates passed on restored D blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.119096 s, M=67,801,088 B, S=783, D=1, K=26.771176, points=71.383372. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-32b27b79a410` on `227bae88c5b80d003fdc3dda193ae499ffc8f66e`; all five gates passed on restored D blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.114928 s, M=67,080,192 B, S=783, D=1, K=27.310621, points=71.816579. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

- Official run `run-ebb1ee6794fc` on `dbbef62bc1668f45d4544f8fde7cb6c758996b68`; all five gates passed on restored D blob `b7a527b058991dce7967738d3695f8ab3917a75d`. T=0.115393 s, M=70,971,392 B, S=783, D=1, K=26.949888, points=71.527848. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).


- Follow-up official run `run-4c526e623c64` on commit `01966dd4c4464d08d4c2a5e44518a351cb102d07` passed all five gates on unchanged D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.111441 s, M=70,815,744 B, S=783, D=1, K=27.435628, points=71.915745. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No source change.


- Official run `run-96ea852ed3a8` on commit `8c51ca2873b18b633fce3f1772a3c6a1a6359b32` passed all five gates on unchanged D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.110937 s, M=71,798,784 B, S=783, D=1, K=27.422165, points=71.905087. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).


## Official rollback checkpoint `cf650cc` — D selected source confirmed

- Board run `run-ae3dba13d81c` on commit `cf650cc6b47038ae06fdf208279d68e2c14355aa` passed all five gates on selected D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.115218 s, M=67,883,008 B, S=783, D=1, K=27.211406, points=71.737549. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Preserve the selected source; this repeat is within observed board variance.


## Official run `5f15f25` — selected D source

- Board run `run-4f05dff0528b` on commit `5f15f2543fbd6a9e18fc3f80490190399322a13d` passed all gates on D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.113161 s, M=78,954,496 B, S=783, D=1, K=26.640330, points=71.276980. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). D source did not change; memory and K remain variable across same-source runs.

## Official run `488ee43` — selected D source

- Board run `run-0aca1692e65f` on commit `488ee43f787334f7c89060ebaaa785e069ea5982` passed all gates on unchanged D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.112188 s, M=70,017,024 B, S=783, D=1, K=27.406238, points=72.086882. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No D source change.

## Official rollback `4b31a19` — selected D source

- Board run `run-1fc107c4dfab` on commit `4b31a195a1c7c4296ca7c3442e774fb9e3e59f91` passed all five gates on unchanged blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.112895 s, M=72,163,328 B, S=783, D=1, K=27.155806, points=71.693135. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No D source change.
