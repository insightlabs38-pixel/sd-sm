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

## Official C-main trial dispatch `5f00315`

- Board run `run-76732f06c07c` on commit `5f00315f8696ca1853c5fb927ad5cd447c6253e9` passed all five gates on unchanged D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.117689 s, M=67,670,016 B, S=783, D=1, K=26.941153, points=71.520809. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). No D source change.

## Official C rollback `9ded4d1` — selected D source

- Board run `run-4d5144409329` passed all gates on unchanged D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.123224 s, M=67,981,312 B, S=783, D=1, K=26.304970, points=71.001890. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official evidence refresh `5d08af1`

- `run-be6a16054ed9` passed all gates on unchanged D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.112260 s, M=68,853,760 B, S=783, D=1, K=27.489403, points=71.958266. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official evidence refresh `89fb2f8`

- `run-94418e148dff` passed all gates on unchanged D blob `b7a527b058991dce7967738d3695f8ab3917a75d`: T=0.117253 s, M=71,929,856 B, S=783, D=1, K=26.663646, points=71.295977. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Team-wide official evaluation `163279d` — unchanged D source

- Source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: run `run-e97a7c209d92` passed all five gates, T=0.111552 s, M=71,442,432 B, S=783, D=1, K=27.373696. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Team-wide official evaluation `3a0273b` — unchanged D source

- Source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: run `run-b6f38e2b8255` passed all five gates, T=0.123351 s, M=67,112,960 B, S=783, D=1, K=26.359110. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## D AVX2 PGO tournament — developer-rejected, not imported

- D main `f3b775e7eeb31d3021299f2fd1bf918a7ba946a1` is a PERF-only handoff. Native 66-pair CI `41307878218` showed gains, but pinned GCC 15 PGO Docker tournament `41308283876` lost; correctness and Docker gates passed, cgroup peak was about 63 MB and scored S/D were unchanged. No source import or official dispatch; retain the selected D champion.

## Team-wide official evaluation `2ace33f` — unchanged D source

- Source blob `b7a527b058991dce7967738d3695f8ab3917a75d`: run `run-68761cd707fc` passed all five gates, T=0.112979 s, M=76,632,064 B, S=783, D=1, K=26.821459. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official team-wide evaluation `77cad4d`

- Run `run-87e86fc988b7` passed all five gates: T=0.112911 s, M=69,922,816 B, S=783, D=1, K=27.325710, points=71.828573. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official team-wide evaluation `96443e0`

- Run `run-608ee1cf998b` passed all five gates: T=0.116239 s, M=75,280,384 B, S=783, D=1, K=26.536954, points=71.192553. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official team-wide evaluation `bfb66b`

- Run `run-887ae7a124a1` passed all five gates: T=0.117828 s, M=74,551,296 B, S=783, D=1, K=26.408764, points=71.087404. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Developer D main handoff `0ae3a2f` — query-order trial rejected

- Main moved from `f3b775e` to docs-only commit `0ae3a2f`; no Track D source changed. Exact workflow `41312677068` succeeded on experiment head `087e72af` with 390 exact full-seed executions plus 88 differential fixtures. Target-ID ordering showed only inconsistent 0.17–0.92% median gains at 6/12 workers, lost paired tests, and regressed at four workers; other tested orderings regressed. Keep D source unchanged; no official submission warranted.

## Official current-source confirmation `97de154` — latest

- Run `run-0eea76e65509` passed all five gates: T=0.123898 s, M=80,650,240 B, S=783, D=1, K=25.351875, points=70.200504. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official D source confirmation `0874d1c` — latest

- Run `run-8599db3389d7` passed all five gates: T=0.127310 s, M=67,735,552 B, S=783, D=1, K=25.898152, points=70.663438. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official source confirmation `3e16ed7` — latest

- Run `run-27c1571288b0` passed all five gates: T=0.115052 s, M=76,578,816 B, S=783, D=1, K=26.582422, points=71.229727. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## Official source confirmation `63f6eed` — latest

- Run `run-b58882ea917b` passed all five gates: T=0.121390 s, M=66,879,488 B, S=783, D=1, K=26.589693, points=71.235666. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). This was a source-identical rerun; it does not validate a new candidate.

## Official source confirmation `f739ccb` — latest

- Run `run-0f52b93868a1` passed all five gates: T=0.113171 s, M=69,185,536 B, S=783, D=1, K=27.352229, points=71.849636. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `dbea191` — latest

- Run `run-dd6d11072ae7` passed all five gates: T=0.110267 s, M=67,792,896 B, S=783, D=1, K=27.822987, points=72.220187. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `ba05448` — latest

- Run `run-0d06324ed749` passed all five gates: T=0.114338 s, M=76,881,920 B, S=783, D=1, K=26.644233, points=71.280161. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `142a9fd` — latest

- Run `run-544f31732267` passed all five gates: T=0.112140 s, M=71,847,936 B, S=783, D=1, K=27.270948, points=71.785011. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `9aaa62c` — latest

- Run `run-887ab3ed7730` passed all five gates: T=0.120887 s, M=72,318,976 B, S=783, D=1, K=26.231499, points=70.941155. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `0a1e4cb` — latest

- Run `run-fe868b4fb8f3` passed all five gates: T=0.111977 s, M=68,096,000 B, S=783, D=1, K=27.585104, points=72.033731. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a new candidate.

## Official source confirmation `7e3b4b6` — latest

- Run `run-8c36ba8b0524` passed all five gates: T=0.115647 s, M=72,204,288 B, S=783, D=1, K=26.827709, points=71.429179. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700). Source-identical rerun, not a D candidate.

## Official source confirmation `7753f18` — latest

- Run `run-008b3a448357` passed all five gates: T=0.119123 s, M=69,971,968 B, S=783, D=1, K=26.599945, points=71.244037. **LATEST**; **BEST** remains `run-4dbbefad4adc` (K=27.644700).

## D main frontier-policy tournament reviewed — 2026-11-01

- Developer main commit `b564f89aea53` records CI 41317136587: 312 exact runs across two seeds, four policies, 4/6/12 workers, plus adversarial/reference gates. Minimum-key regressed at every configuration; queue-size balancing was seed/worker inconsistent and the hybrid also lacked consistent gains. The source was not promoted; no official dispatch is warranted. Keep official fused-PGO source blob `b7a527b058991dce7967738d3695f8ab3917a75d` and its recorded BEST `run-4dbbefad4adc`.


## Track D baseline before developer-main batch-16 validation (2026-11-01)

- Existing official D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; run `run-d00e1b74e673` on commit `c1c2c9fdd77044d39c4f433b0400aad1ed7c267a` passed all five gates: T=0.115313 s, M=76,972,032 B, S=783, D=1, K=26.525137, points=71.182882.
- BEST remains `run-dd6d11072ae7`, K=27.822987. This baseline is retained for rollback comparison.

## Developer-main D fused batch-16 candidate queued for official trial

- Candidate source blob `09270462259085787ac2925485b5e1cd7e56647f` from developer main `0a8077f50a47e308c6297c7de4c29c3da6bb59ab`. It applies the qualified four-worker graph-construction cap and changes fused BFS growth batch 32→16; no Dockerfile/dependency change.
- Developer CI `41322761850` and pinned GCC15 PGO Docker confirmation `41323248319` passed 88 differential fixtures, official sample/full hashes and exact seed-1/7 output checks. In PGO Docker, 55/66 paired runs won, medians improved 0.41–2.64%, cgroup peak stayed about 63.0 MB; S and D unchanged. This is not official scoring-box evidence. Official trial is pending.


## Developer-main D batch-16 official trial — rejected (2026-11-01)

- Candidate blob `09270462259085787ac2925485b5e1cd7e56647f` from developer-main `0a8077f50a47e308c6297c7de4c29c3da6bb59ab` passed all official gates on `run-9b7f0c04b812`, commit `0df4790f0becf12bb8935e6edc9470873d73c406`: T=0.157752 s, M=65,863,680 B, S=784, D=1, K=23.391797.
- Against D BEST `run-dd6d11072ae7` (K=27.822987), K regressed 15.9%; versus the preceding D baseline run `run-d00e1b74e673`, T increased 36.8% while M fell 14.4% and S grew by one line. Despite strong developer PGO/local receipts, the scoring-box result rejects this source combination. Restore official source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; developer main remains untouched.


## Official D champion confirmation after batch-16 rejection (2026-11-01)

- Restored source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; run `run-3296866f16a0` on commit `39bc3db91faaa25fcaf344a62c3f973ed6ff8a9e` passed all five gates: T=0.111487 s, M=71,086,080 B, S=783, D=1, K=27.409072. **BEST** remains `run-dd6d11072ae7`, K=27.822987.


## Team-wide run during B main-source trial (2026-11-01)

- Unchanged selected D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; run `run-8d101a7f289e` on commit `6cb6df52c71f607af145c164a40fef274eea3c95` passed all five gates: T=0.114714 s, M=71,438,336 B, S=783, D=1, K=26.994102. **BEST** remains `run-dd6d11072ae7`, K=27.822987.


## Exact current-head rerun after B source trial (2026-11-01)

- Unchanged selected D blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-6f5532ab0976` on `d90da4f39ac3c9cda07fbc7f57f816dc19976a25` passed all five gates: T=0.112395 s, M=69,672,960 B, S=783, D=1, K=27.407979. **BEST** remains `run-dd6d11072ae7`, K=27.822987.


## Exact current-head rerun 2026-11-01

- Selected source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-f8ef208994d3` on `45e8a07f2baad5113c6b858e2d3576b6db29a436` passed all five gates: T=0.124824 s, M=71,680,000 B, S=783, D=1, K=25.860369. **BEST** remains `run-dd6d11072ae7`, K=27.822987.

## Exact current-head run after receipt update (2026-11-01)

- Selected source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-14cfb6918691` on `f3e5fbd8ece8535c3142c8a914813075dddff341` passed all five gates: T=0.110874 s, M=67,993,600 B, S=783, D=1, K=27.730321, points=72.147745. **BEST** remains `run-dd6d11072ae7` (K=27.822987); this is **LATEST**.

## All-track rerun during A PR #4 trial (2026-11-01)

- Unchanged D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-2889233f342e` on official commit `18d16b927ac28c90205dbfe4934b5951f0cfea48` passed all five gates: T=0.115814 s, M=74,244,096 B, S=783, D=1, K=26.659405, points=71.292522. This is **LATEST**, not BEST `run-dd6d11072ae7` (K=27.822987); source is unchanged from `run-14cfb6918691` (K=27.730321). Record the memory/time variance; do not infer a D code regression from A's edit.

- Source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-bf8f4f1cf152` on commit `f8e388471260b59810b9974252b8a5d8bfe8d5ec` passed all five gates: T=0.112690 s, M=72,237,056 B, S=783, D=1, K=27.174944, points=71.708433. **LATEST**; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

- Unchanged D source blob `b7a527b058991dce7967738d3695f8ab3917a75d`; `run-3cd9c8d28fb9` on `b098465d9c206e5f25fe2ccb1996689a1d676302` passed all five gates: T=0.118803 s, M=69,218,304 B, S=783, D=1, K=26.693497, points=71.320273. **LATEST at that head**; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

- `run-b557a21e8359` on `ab84ec24be844316a3a88a8e8ad2edaca5824e88` also passed all five gates on unchanged D source: T=0.116566 s, M=67,391,488 B, S=783, D=1, K=27.092957, points=71.642820. **LATEST**; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — 2026-11-01, commit `9dcde1dd1cedf6e421c55f8bb29b66a8c31544fa`

- **LATEST:** `run-61b4e6efd4e1`; T=0.110851 s, M=69,697,536 bytes, S=783, D=1, K=27.596250, points=72.042503; check/build/correctness/timeout/sandbox gates all passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -0.81% versus BEST. Versus prior receipt `run-bf8f4f1cf152` (K=27.174944), latest K changed +1.55%.
- Source snapshot: A `c91` / B `b8ef` / C `0772` / D `b7`. No source promotion or PR merge from this run.

## Official board receipt — 2026-11-01, commit `d04c1c7fac73ba0b433fc978ca17ea73ba15a6ff`

- **LATEST:** `run-e71ef96d4d83`; T=0.120924 s, M=72,404,992 bytes, S=783, D=1, K=26.221251, points=70.932670; check/build/correctness/timeout/sandbox gates all passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -5.76% versus BEST. Against preceding same-source receipt `run-61b4e6efd4e1` (K=27.596250), K changed -4.98%; these measurements do not support a source promotion.
- Sources unchanged: A `c91` / B `b8ef` / C `0772` / D `b7`; no PR merged.

## Official board receipt — 2026-11-01, commit `542794bc00d4d346b65976f073a5f2cf1ec22593`

- **LATEST:** `run-3925ebc17933`; T=0.113608 s, M=69,828,608 bytes, S=783, D=1, K=27.249104, points=71.767611; all five gates passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -2.06% versus BEST. Against preceding same-source run `run-e71ef96d4d83` (K=26.221251), K changed +3.92%; source unchanged.
- No source promotion or PR merge is supported by this run.

## Official board receipt — 2026-11-01, commit `269e0bb26368cb0d38f492561d8f11ab8b47a131`

- **LATEST:** `run-50fee11bc27f`; T=0.122314 s, M=74,018,816 bytes, S=783, D=1, K=25.957141, points=70.712843; all five gates passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -6.71% versus BEST. Against preceding same-source run `run-3925ebc17933` (K=27.249104), K changed -4.74%; source unchanged.
- No source promotion or PR merge is supported by this run.

## Official board receipt — 2026-11-01, commit `33914daf6197af1b5f3fbf564accbbf217b9b882`

- **LATEST:** `run-d4ccae117bbd`; T=0.113527 s, M=67,993,600 bytes, S=783, D=1, K=27.404392, points=71.891009; all five gates passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -1.50% versus BEST. Against preceding same-source run `run-50fee11bc27f` (K=25.957141), K changed +5.58%; source unchanged.
- This source-identical rerun does not support promoting an open candidate.

## Official board receipt — 2026-11-01, commit `c97e128f086a883ce4a9b6287e345e6fce3b9565`

- **LATEST:** `run-4abd32d13ea4`; T=0.115180 s, M=74,231,808 bytes, S=783, D=1, K=26.733561, points=71.352841; all five gates passed.
- **BEST remains:** `run-dd6d11072ae7`, K=27.822987; latest K is -3.92% versus BEST. Against preceding same-source run `run-d4ccae117bbd` (K=27.404392), K changed -2.45%.
- This source-identical rerun provides no promotion evidence.

## Official board receipt — 2026-11-01, commit `43bdf2bbd64d9cdae24291dfe71431154bab61cf`

- **LATEST before the A PR #7 trial:** `run-29f2f8902f41`; T=0.118785 s, M=67,641,344 B, S=783, D=1, K=26.818848, points=71.422006; all five gates passed. Source D remained `b7` and BEST remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — all-track rerun, commit `65ac364be8965ab62a3ba737882b630a4bb126ae`

- `run-ae3888816b8a`: T=0.130222 s, M=66,637,824 B, S=783, D=1, K=25.690764, points=70.488851; all gates passed.

## Official board receipt — all-track rerun, commit `cffcacbe03237196298ec5c5e302392ec24f865d`

- **LATEST before this trial:** `run-0368eed6d813` on source `b7a527b0` with BATCH=32: T=0.113547 s, M=76,890,112 B, S=783, D=1, K=26.736308, points=71.355072; all five gates passed. **BEST remains** `run-dd6d11072ae7`, K=27.822987.

## Official trial — D batch size 8 against current official source (2026-11-01)

- Based on merged `sd-td` PR #14 / main (`c8a929f60c6a69708b09eac228145b7970273c10`, source blob `55daa262f2916e61373922fbe4af41a9a4de5edf`), but imported only the `BATCH` tuning. Official source blob before this change was `b7a527b058991dce7967738d3695f8ab3917a75d` at BATCH=32; this trial tests 32→8, not the developer's measured 16→8 comparison.
- Developer PERF reports 312 native paired comparisons (49/78 wins) and 234 pinned-PGO exact executions (52/78; all six medians 0.22–0.73% faster) for 16→8, with 88 differential fixtures per PGO variant and offline pinned Docker validation. Those measurements do not establish 32→8 performance on this official source.
- Candidate source size and dependencies are unchanged. **Official result pending; promote only if its scored K and other axes justify it.**

## Official board receipt — D batch-size 8 trial, commit `5b45d276d3f038daebbf8c290ea021507086b456`

- `run-40a4a435db56` passed all five gates: T=0.112692 s, M=72,306,688 B, S=783, D=1, K=27.169467, points=71.704056. This is +1.62% K versus immediate BATCH=32 run `run-0368eed6d813` (K=26.736308), but -2.35% versus D BEST `run-dd6d11072ae7` (K=27.822987); BEST also has faster T (0.110267 s) and lower M (67,792,896 B). **Decision: not promoted.** Restored BATCH=32 source blob `b7a527b058991dce7967738d3695f8ab3917a75d`.

## Official board receipt — rollback checkpoint `cdd6fd395d013eb19d3bd2ff7917c4e1ceea50e9`

- `run-8cb7666cafd2` passed all five board gates: T=0.112756 s, M=75,509,760 B, S=783, D=1, K=26.927307, points=71.509646. **LATEST**; **BEST** remains `run-dd6d11072ae7` (K=27.822987). Source is restored known-good blob `b7a527b058991dce7967738d3695f8ab3917a75d` (BATCH=32); the BATCH=8 candidate did not beat BEST.

## Official board receipt — B row-prefetch trial, commit `aac3a059e93d5b8b31ea9cef2b1522398ef6b593`

- `run-99ac15c0ae90` passed all five gates: T=0.117556 s, M=68,866,048 B, S=783, D=1, K=26.862098, points=71.456997. D source unchanged; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — Track B restored-source comparison, commit `f00fe1077308e74fbf82bc75a3cb311502de4a7c`

- `run-ed1320513986` passed all five gates: T=0.113112 s, M=78,204,928 B, S=783, D=1, K=26.696984, points=71.323110. D source unchanged; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — Track B row-prefetch confirmation, commit `b6f4226481a9adf8d9dbddcac3f6d67593de62c3`

- `run-539656fbc6d1` passed all five gates: T=0.112623 s, M=76,148,736 B, S=783, D=1, K=26.897832, points=71.485864. D source unchanged; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — Track B champion rollback, commit `021d3bbbbb502e762e7402f38ff341f67bccd377`

- `run-5208b85aaecd` passed all five gates: T=0.122566 s, M=73,846,784 B, S=783, D=1, K=25.942513, points=70.700602. D source unchanged; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official board receipt — pre-D-PR #15 baseline, commit `c0bce0d013a45775ce9d470f0c33b774a28fc0a2`

- `run-6e60489bf617` passed all five gates: T=0.124494 s, M=67,547,136 B, S=783, D=1, K=26.204010, points=70.918388. D source is champion blob `b7a527b058991dce7967738d3695f8ab3917a75d`; **BEST** remains `run-dd6d11072ae7` (K=27.822987).

## Official trial — D PR #15 lean CSR challenger

- Imported only the solution and Dockerfile from draft PR #15 head `19664ab0802e743e613940f13a70f21bb419abf2`: `d_traverse.cpp` blob `e43f8538f6c26f91681dc96b67a350ae73ed50da`, Dockerfile blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. The candidate stays within the pinned GCC 15 / Debian 13 image pair and builds `/traverse` with the official flags. The unrelated candidate tests, README and research were not imported.
- PR-reported local evidence (not official board evidence): 5 Docker cgroup runs peak 59.2–59.4 MB vs champion 65.9–66.2 MB; native 12-worker median 519–527 ms vs 540 ms; exact output on full seeds 1/7/17 and sample/tiny seeds, 88 differential cases, 150 stress seeds, 60 2^32-boundary cases, sanitizer and pinned-Docker checks. Current PR head has no GitHub status checks; this official board trial is the independent validation.
- PR projects 6–9% higher K than the current D source. **BEST before trial** remains `run-dd6d11072ae7` (K=27.822987). Candidate not promoted until actual official gates and score are reviewed; rollback parent `c0bce0d013a45775ce9d470f0c33b774a28fc0a2` contains champion source blob `b7a527b058991dce7967738d3695f8ab3917a75d` and its Dockerfile.

## Official board receipt — D PR #15 BATCH=32 trial, commit `fb66a3774da75cd6cbe47b6b6a3f90d4eba930ca`

- `run-b1194463b02c` passed all five gates: T=0.111112 s, M=61,321,216 B, S=592, D=1, K=29.490133, points=73.483837. Relative to prior BEST `run-dd6d11072ae7` (K=27.822987, T=0.110267, M=67,792,896, S=783), K improved 5.99%, M fell 9.55%, S fell 24.39%, and T was 0.77% slower. **BEST is now `run-b1194463b02c`.**

## Official trial — D PR #15 eight-vertex growth batches

- Current draft PR head `484035cd6e8059b9e13db187bcd248d310400b83`, source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`, changes only the lean candidate's growth batch from 32 to 8; pinned Dockerfile blob remains `8eabe09b96a60131ce5bfda3f098011e1f0863e6`.
- Developer's latest paired 4-vCPU local comparison reports wall time 1.6%/3% lower at 4/12 workers, with 7/13 and 7/11 wins respectively. This is local evidence, not an official score; the PR head has no current GitHub checks. Official build/correctness/timeout/sandbox gates will evaluate this exact variant.
- Rollback parent `fb66a3774da75cd6cbe47b6b6a3f90d4eba930ca` retains D PR #15's BATCH=32 source (blob `e43f8538f6c26f91681dc96b67a350ae73ed50da`), which is already the official BEST source at this point.

## Official board receipt — D PR #15 BATCH=8 trial, commit `eb21daa231bb1bddad8c277f186cd516c05025d4`

- `run-9757529e8b52` passed all five gates: T=0.108321 s, M=60,317,696 B, S=592, D=1, K=29.966367, points=73.831705. Compared with the official BATCH=32 CSR run `run-b1194463b02c` (K=29.490133, T=0.111112, M=61,321,216 B, S=592), K improved 1.61%, T improved 2.51%, M fell 1.64%, and S was unchanged. Compared with original D BEST `run-dd6d11072ae7` (K=27.822987, T=0.110267, M=67,792,896 B, S=783), K improved 7.70%, M fell 11.03%, S fell 24.39%, and T was 1.76% faster. **BEST is now `run-9757529e8b52`.**
- Promoted PR #15 after this exact head/source/Dockerfile passed the official board: GitHub merge `e1be6c6ea78b8ed8214fe1992759e87bd25db51a`. Source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`; Dockerfile blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. Official image remains pinned GCC 15 / Debian 13.

## Official board receipt — D promotion checkpoint, commit `650272f4043d367210da65af1ca0d8f07f640f5f`

- `run-721f03e8045e` passed all five gates: T=0.109751 s, M=61,583,360 B, S=592, D=1, K=29.647116, points=73.599123. **LATEST** for the promoted PR #15 BATCH=8 source; **BEST remains** `run-9757529e8b52` (K=29.966367).

## Official board receipt — A PR #5 trial all-track run, commit `54b423edcac810adb53fb4c746152dc356296984`

- `run-cde04baf80e2`: T=`0.108166 s`, M=`60,473,344 B`, S=`592`, D=1, K=`29.972377`, points=`73.836059`; all five gates passed. D source unchanged. This is a +0.020% K noise-sized increase over former BEST `run-9757529e8b52` (K=`29.966367`); record `run-cde04baf80e2` as raw BEST and LATEST, with no new source promotion.

## Official board receipt — A PR #4 trial all-track run, commit `9cf30b881155c2749c40646b293f911e77ebfe2d`

- `run-3e199f6334fa`: T=`0.112805 s`, M=`60,862,464 B`, S=`592`, D=1, K=`29.311989`, points=`73.352264`; all five gates passed. D source unchanged; BEST remains `run-cde04baf80e2` (K=`29.972377`).


## Official all-track receipt — A PR #6 trial, commit `32a2c5f2192e5ead9bc480c1392f6dc2a741cee2`

- `run-e09b1c34dd63` passed all five gates: T=0.107637 s, M=60,530,688 B, S=592, D=1, K=30.040244, points=73.885173. On unchanged D source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`, this is 0.23% above prior same-source BEST `run-cde04baf80e2` (K=29.972377); record `run-e09b1c34dd63` as the new raw BEST and LATEST. No D source promotion is implied.


## Official all-track receipt — A PR #7 trial, commit `81943ddb059636a4ae357613c0a887beb688e7db`

- `run-f25900fc870c` passed all five gates: T=0.112543 s, M=60,497,920 B, S=592, D=1, K=29.381370, points=73.403602. D source remained unchanged; **BEST** remains `run-e09b1c34dd63` (K=30.040244) and **LATEST** is `run-f25900fc870c`.


## Official all-track receipt — C main trial, commit `b9012e5073ea49c8f6e39079bfc43b4953eb6b2b`

- `run-3d2e9d913d87` passed all five gates on unchanged D source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`: T=0.106435 s, M=60,674,048 B, S=592, D=1, K=30.195105, points=73.996827. This is 0.52% above previous same-source BEST `run-e09b1c34dd63` (K=30.040244); record `run-3d2e9d913d87` as raw **BEST** and **LATEST**. No D source change.

## Official all-track receipt — restored selected tree, commit `199e41df4695b591c909b064af49fb80ecd1388b`

- `run-bee999330bf5` passed build, check, correctness, timeout, and sandbox gates: T=0.117102 s, M=60,456,960 B, S=592, D=1, K=28.807658, points=72.975398. D source remained selected blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`; LATEST is this run. BEST remains same-source `run-3d2e9d913d87` (K=30.195105); this result is 4.60% below BEST.

## Official all-track receipt — evidence checkpoint `d70ce847a8dbef1a2881a017207d5ecb4f520d9f`

- `run-1827e854c0d6` passed all five gates on unchanged D source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`: T=0.113914 s, M=60,837,888 B, S=592, D=1, K=29.171314, points=73.247800. **LATEST** is this run; **BEST** remains `run-3d2e9d913d87` (K=30.195105), 3.39% higher.

## Official all-track receipt — checkpoint `2470b6250a0cd834661b1ca5b21def7b4703ef50`

- `run-f5f113b794a4` passed all five gates on unchanged D source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`: T=0.106670 s, M=61,198,336 B, S=592, D=1, K=30.109968, points=73.935515. **LATEST** is this run; **BEST** remains `run-3d2e9d913d87` (K=30.195105).

## Official all-track receipt — checkpoint `19582b89b83bb4bdc46998fdbcd9c7d0fb7baadd`

- `run-820dca3523c4` passed all five gates on unchanged D source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`: T=0.116555 s, M=61,583,360 B, S=592, D=1, K=28.768766, points=72.946062. **LATEST** is this run; **BEST** remains `run-3d2e9d913d87` (K=30.195105).

## Official trial — D PR #18 c2-cap4 architecture (rejected)

- Exact candidate source blob `5df4bde3f8e46a32335ef380ed0cf4cf85415bf1` from `sd-td` PR #18 head `32e58c9a991038001f23cd49f726973c7c00489c`; only `d_traverse.cpp` imported. Dockerfile unchanged at pinned GCC 15/Debian 13 blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`.
- Exact-source qualification CI `41361643036` passed randomized/adversarial differential tests, official cases and hashes, pinned Docker full/sample output comparisons, and 1/4/12-worker correctness. Paired runner experiment `41360802889` reports exact outputs; versus PR #15, median wall reductions at 4/6/12 workers were 5.70/8.39/7.37% on seed 1 and 5.48/7.78/6.12% on seed 7. The 4-vCPU runner may overstate the 4-worker construction cap's advantage on the 12-thread board. Source S=609, D=1. These are developer measurements, not official K.
- Official run `run-685fc910bcd1` on commit `bc7dcf4d5ec5f0a9da9db0018c83a89f712c38d0` passed all five gates, but measured T=0.147556 s, M=59,510,784 B, S=609, D=1, K=25.635244, points=70.441873. It is 15.10% below **BEST** `run-3d2e9d913d87` (K=30.195105) and 10.89% below the prior **LATEST** `run-820dca3523c4` (K=28.768766); reject PR #18 and restore the known-good source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`. This official result overrides the favorable 4-vCPU paired measurements for the capped construction variant.


## Official trial — D PR #17 uncapped c2 (six official samples; main cap-4 rejected)

- Candidate source blob `79617b5c40b01613797138b294a33c0a7b5c6e44` from fresh, ready PR #17 head `9e8e5129321a22713a27fb77bb0d0f15b75db29a`; exact qualification check passed. Its 13-round paired runner reports exact outputs and median wall-time gains vs PR #15 of 3.30–5.93% across 4/6/12 workers, with max RSS within 0.6 MB; independent 4-vCPU KVM trials report 3.1–10.5% wall-time gains. Unlike rejected PR #18, it does not cap construction at four workers. These are developer measurements, not official K. Rollback remains blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`; promote only if official D K beats BEST and every gate passes.

- Official `run-fec0ec78f97e` on exact PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44` passed all five gates: T=0.103011 s, M=60,162,048 B, S=607, D=1, K=30.629718, points=74.307150. This becomes numeric **BEST** and **LATEST**, 1.44% above prior BEST `run-3d2e9d913d87` (K=30.195105). The first result is inside the source-identical scoring spread; a repeat follows below. Keep the exact candidate for comparison with current main; do not merge PR #17 until the alternative is measured. Original rollback remains the qualified selected source blob `d0a25aea3da74f7e9031c5591ecf1524049675ed`.

- Repeat official run `run-2ce6b57e8f7c` on commit `648afc7992a40d79ead4e56abe7abe56d310017a` passed all five gates: T=0.105065 s, M=60,682,240 B, S=607, D=1, K=30.276660, points=74.055399. **LATEST**; numeric **BEST** remains `run-fec0ec78f97e` (K=30.629718) on this exact PR #17 source. Both official PR #17 samples exceed the former D BEST `run-3d2e9d913d87` (K=30.195105); retain this source as rollback while testing main.

## D main cap-4 trial — rejected; restored PR #17

- Exact source blob `fcd4c4e7c1ed0a58807675503ac8cee2b8d4b93d` from `sd-td/main` head `4812c263bb2bc9f0dbc769942b7651132766b30e`; exact main-source CI and the developer's pinned-Docker qualification passed. The cap tournament supported an official comparison, while its local K projection was not an official score.
- Local verification attempt: the host `g++ -O3 -std=c++17 -pthread -flto -static -s` compile succeeded (GCC 14.2); a pinned-image Docker rebuild failed during layer registration with `no space left on device` in the Docker storage area. This is an environment limit, not a source/test failure; exact-source pinned Docker CI had passed.
- Official `run-53d5402123e9` on commit `27d732ecd32dcda88f7e2dd00e2bfc1ba08e3477` passed all five gates: T=0.157924 s, M=59,768,832 B, S=594, D=1, K=24.850815, points=69.767032. This is current D/global **LATEST** and is 18.87% below the uncapped PR #17 repeat `run-2ce6b57e8f7c` (K=30.276660) and 18.87% below D BEST `run-fec0ec78f97e` (K=30.629718); reject D main cap-4 despite its lower S and passing correctness gates. Restore PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`; retain `run-fec0ec78f97e` as numeric BEST and `run-2ce6b57e8f7c` as PR #17 LATEST at the time of the D-main comparison; the restored-source run is recorded below.

## Official all-track receipt — restored D PR #17, commit `a2c7057b631abd61ed3618f7a8f621fa69b3f3ea`

- `run-44ee0b002e5a` passed all five gates on restored PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`: T=0.104978 s, M=60,493,824 B, S=607, D=1, K=30.308048, points=74.077898. This is **LATEST** and remains below numeric **BEST** `run-fec0ec78f97e` (K=30.629718); it beats the previous D BEST `run-3d2e9d913d87` (K=30.195105) by 0.37%. At that point three official PR #17 source runs were 30.629718, 30.276660, and 30.308048 (median 30.308048). Subsequent same-source runs are recorded below. Keep PR #17 source as current selected D champion; do not claim any historical run as the frozen commit's final score.

## Official all-track receipt — PR #17 source repeat, run-log commit `770ff3ed22aef6d4cb07026aa0a07e2c3ded7911`

- `run-1b8d7ec1c331` passed all five gates on unchanged PR #17 D source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`: T=0.099925 s, M=60,354,560 B, S=607, D=1, K=31.079228, points=74.623511. This becomes **BEST** and **LATEST**, improving prior numeric BEST `run-fec0ec78f97e` (K=30.629718) by 1.47%. The run-log commit changed no solution source; exact PR #17 code remains the scored candidate.

## Official all-track receipt — D README/performance-log checkpoint `5e2c127efce867d05e8bee41d20d5b7f0a058d21`

- `run-127fca336dc8` passed all five gates on unchanged PR #17 D source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`: T=0.102920 s, M=60,059,648 B, S=607, D=1, K=30.653698, points=74.324144. **LATEST**; **BEST** remains `run-1b8d7ec1c331` (K=31.079228). The source-identical PR #17 sequence is K=30.629718, 30.276660, 30.308048, 31.079228, 30.653698; median K=30.629718. This repeated evidence keeps PR #17 ahead of the old selected source without treating the highest single run as the frozen score.

## Official all-track receipt — D PR #17 outcome checkpoint `128993129f41ea3cc850aaadcfccf1f4a3b8f791`

- `run-f74487302b35` passed all five gates on unchanged PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`: T=0.102394 s, M=60,309,504 B, S=607, D=1, K=30.706825, points=74.361746. **LATEST**; **BEST** remains `run-1b8d7ec1c331` (K=31.079228). This gives six source-identical official PR #17 K samples; their median is 30.641708. The sixth remains above the former selected D BEST 30.195105.

## Frontier trial — D PR #19 equal-slice renaming and recycled pages (not yet official)

- Exact source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097` from ready PR #19 head `d6cceafd15e6f24d5aa713f4f3a6fb2711753f5c`, based on D main `ede72218d675fea1dce189fb6ce6a278d78e4e84`. Imported only `d_traverse.cpp` and the matching README; official Dockerfile remains pinned GCC 15/Debian 13 blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. Source size is S=643 including Dockerfile (+36 vs PR #17, S=607); D=1.
- Developer reports 21 interleaved full seed-1 rounds on a 4-vCPU runner: wall time -9.6% at 12 workers (17/21 wins) and -11.6% at 4 workers (17/21). Reported 12-worker cgroup peak 58.4–59.3 MB vs 58.5 MB for PR #17. This is local evidence, not official K.
- Developer reports exact full seeds 1/7 at 1/4/12 workers, sample seed 1 reference parity, 88 differential, 60 boundary and 30 stress tests, and clean ASan/UBSan/TSan. No GitHub CI status was registered for this PR at integration; host GCC 14.2 pinned-flag compile succeeded locally. Local Docker replay is unavailable because the daemon storage previously failed layer registration with `no space left on device`.
- Official comparison baseline: restored PR #17 `run-f74487302b35` K=30.706825 and BEST `run-1b8d7ec1c331` K=31.079228. Keep rollback source blob `79617b5c40b01613797138b294a33c0a7b5c6e44`; select PR #19 only if official all-gates K is a repeatable improvement.


## Official trial — D PR #19 equal-slice/recycled-page construction

- Submission commit `798c15d26ee3132bbc5d29541ee3d1de2534839a` used candidate source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097`, with the pinned Dockerfile unchanged. Official `run-e708fb9cfacc` passed all five gates: T=0.092567 s, M=60,915,712 B, S=649, D=1, K=31.909277, points=75.195848. **LATEST and provisional BEST**; previous BEST `run-1b8d7ec1c331` was K=31.079228, T=0.099925 s, M=60,354,560 B, S=607, D=1. Against the previous LATEST `run-f74487302b35` (K=30.706825, T=0.102394 s, M=60,309,504 B, S=607), this sample improves K 3.92% and lowers T 9.60%, at +606,208 B peak memory and +42 S.
- One official sample is not yet a stable champion estimate; keep PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44` as the rollback. The candidate’s reported multi-seed correctness/stress and sanitizer checks are developer evidence; this invocation independently confirmed the source blob and a host compile. Pinned GCC15 Docker build was attempted but could not register a GCC layer because the local Docker daemon returned `no space left on device`; no local Docker pass is claimed.


## Official repeat — D PR #19 equal-slice/recycled-page construction

- Submission commit `2d6609b2d6a26f79b20b3df8a5dc2dbd9fa6f7e6` repeated the same candidate source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097`; pinned Dockerfile remained unchanged. `run-aeaaa695cf19` passed all five gates: T=0.095627 s, M=61,374,464 B, S=649, D=1, K=31.347515, points=74.810156. **LATEST**; **BEST** remains `run-e708fb9cfacc` (K=31.909277). This is the second consecutive official full-seed-1 score above the previous D BEST `run-1b8d7ec1c331` (K=31.079228); both PR #19 samples pass every gate. Two-sample mean K=31.628396 vs the previous six-sample PR #17 median 30.641708 (+3.22%); the latest sample remains 0.86% above the prior BEST. PR #17 source blob `79617b5c40b01613797138b294a33c0a7b5c6e44` remains the rollback.

## Frontier trial — D PR #20 saturated labels and constant queue keys

- Exact candidate is PR #20 head `219ec2ebb38a6a34d54aa7b56bf9698f557f2922`, source blob `55f5221730afa74a362278adb94f2eb5ef2f6ee0`; Dockerfile remains pinned blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. Developer estimates S=605 including Dockerfile and D=1; official run will determine measured S/K.
- Qualification workflow `41366359681` completed successfully: exact pinned Docker build, differential/boundary/contraction stress, organizer reference/worker matrix in restricted Docker, and ASan/UBSan plus TSan oracle fixtures all passed. A local static host-GCC compile also succeeded. The local Docker daemon cannot complete GCC layer registration because its filesystem reports `no space left on device`; no local Docker pass is claimed.
- PR reports an initial 3–4% lower whole-program time on a two-CPU guest; this is not an official K claim or a board-topology match. Official comparison is warranted because the change is fresh, has full qualification gates, and reduces estimated S relative to PR #17. Keep PR #19 source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097` as rollback; its official samples `run-e708fb9cfacc` and `run-aeaaa695cf19` scored K=31.909277 and 31.347515, both above prior BEST 31.079228.


## Official trial — D PR #20 saturated labels / constant queue keys

- Submission commit `a8ff46e16509338f515a4569f0de934e175825a5` used source blob `55f5221730afa74a362278adb94f2eb5ef2f6ee0`; pinned Dockerfile blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. `run-101d854c9cfc` passed all five gates: T=0.099084 s, M=60,166,144 B, S=605, D=1, K=31.245834, points=74.739606. **LATEST**; **BEST** remains PR #19 `run-e708fb9cfacc` (K=31.909277).
- This one PR #20 sample is 0.54% above former PR #17 BEST `run-1b8d7ec1c331` (K=31.079228), but below both official PR #19 samples (K=31.909277 and 31.347515; mean 31.628396). It reduces measured S 44 and peak M by 749,568–1,208,320 B versus those PR #19 runs, while T=0.099084 s is slower than their 0.092567/0.095627 s. Repeat before selecting; rollback source remains PR #19 blob `15e1a45dec8f2272c965ca3b3d70b3928f872097`.

## Frontier trial — D PR #23 combined construction and saturated-label queries

- Exact candidate is PR #23 ready head `c90d258d070e3a4b56c53d8ab2be9feb3199e735`, source blob `e11b09e30d2ac0fdfada01317b5dce3deae5f6dd`; unchanged pinned Dockerfile blob `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. Developer estimates S=641 and D=1. This combines PR #19 equal-slice/recycled-page construction with PR #20 saturated labels/constant queue keys; rollback sources are PR #19 `15e1a45dec8f2272c965ca3b3d70b3928f872097` and PR #17 `79617b5c40b01613797138b294a33c0a7b5c6e44`.
- Developer’s linked 11-round pinned-GCC15 benchmark on a qualification branch reports exact outputs and 11/11 wins in each worker/seed cell; wall time vs c2 improves 12.24–14.33% at 4/6/12 workers across full seeds 1 and 7. The same comparison reports PR #19 alone at -8.3% to -10.6%, PR #20 alone at -3.4% to -4.8%, with peak cgroup M=58.4–58.7 MB vs c2 58.5 MB. Developer also reports exact full seeds 1/7 at 1/4/12 workers, sample 1, 88 differential, 60 boundary, 30 stress, 110 saturation tests, ASan/UBSan/TSan and pinned offline Docker parity. These are developer qualification results, not official K.
- Exact source blob was independently checked against the ready PR head and compiled statically with host GCC. Local official pinned-Docker replay remains blocked by the daemon’s `no space left on device` layer-registration failure; the official board build/gates will be authoritative. Submit for official comparison because the combined full-seed claim is materially stronger than either parent candidate.


## Official trial — D PR #23 combined construction and saturated-label queries

- Submission commit `a5b6172a946ed30ffc912ea7e2c09474851e6768` used source blob `e11b09e30d2ac0fdfada01317b5dce3deae5f6dd`; unchanged pinned Dockerfile. `run-7cbf51892a7c` passed all five gates: T=0.088389 s, M=60,166,144 B, S=647, D=1, K=32.750840, points=75.761122. **LATEST and BEST**. Compared with prior BEST PR #19 `run-e708fb9cfacc` (K=31.909277), K improves 2.64%, T improves 4.52%, M falls 749,568 B and S falls by 2. It also beats former PR #17 BEST `run-1b8d7ec1c331` (K=31.079228) by 5.37%. Keep PR #19 source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097` as rollback.

## Frontier trial — D PR #22 x86-64-v3 build of equal-slice construction

- Exact PR #22 ready head `70a3a81963445db3e90cd9ddb4e41efd1569565e`: source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097` (same as PR #19), README blob `9c6f49b46513f3422476beac1500455e71ccd30e`; Dockerfile blob `86317a4ba941ba9576a7be479f3fb4c0fd51230a` adds `-march=x86-64-v3`. Developer reports S=643, D=1; the live board will measure S. Board i5-13500 supports the v3 ISA features.
- Developer reports 21 interleaved local rounds on 4 vCPUs: wall -6.5% at 12 workers (14/21 wins), -8.5% at 4 workers (13/21), CPU -4.5% (12/15); exact full seeds 1/7 at 1/4/12 workers, 88 differential, 60 boundary and 30 stress tests, pinned offline Docker and board-style parity. The older Oct 31 test on an older source showed no v3 gain, so this trial is scoped to the newer PR #19 source. These are local results, not official K.
- Host compile with the exact x86-64-v3 flags succeeded. Local Docker daemon still cannot register the pinned GCC layer (`no space left on device`); no local Docker pass is claimed. Official rollback is PR #23 source blob `e11b09e30d2ac0fdfada01317b5dce3deae5f6dd` with Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6` (BEST run `run-7cbf51892a7c`, K=32.750840).

## Official latest run — D PR #22 build-flag trial

Commit `56f3cabeab3c780111683a9b9f67e6b54dc824b9` used PR #22 source blob `15e1a45dec8f2272c965ca3b3d70b3928f872097` and Dockerfile blob `86317a4ba941ba9576a7be479f3fb4c0fd51230a` (`-march=x86-64-v3`). `run-34ed1558cbbb` passed check/build/correctness/timeout/sandbox: K=32.034892, T=0.091404 s, M=61,648,896 B, S=649, D=1, points=75.281163. This is LATEST; BEST remains PR #23 `run-7cbf51892a7c` at K=32.750840, T=0.088389 s, M=60,166,144 B, S=647. PR #22 is down 2.19% in K, 3.41% slower in T, uses 1,482,752 B more memory and adds 2 source lines. Do not promote; preserve PR #23 as champion/rollback.

## Current official candidate restored after PR #22

PR #22 failed to beat BEST, so the official submission source is restored to PR #23 blobs from known-good commit `a5b6172a946ed30ffc912ea7e2c09474851e6768`: `d_traverse.cpp` `e11b09e30d2ac0fdfada01317b5dce3deae5f6dd`, Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. At rollback time PR #23 `run-7cbf51892a7c` (K=32.750840) was BEST; a later same-source repeat, `run-b2b5c42472eb`, raised the current BEST to K=32.868729. PR #22 `run-34ed1558cbbb` remains a failed trial.

## Official champion-restoration run — `8fc0d908aeadb934648e44e70f1e0dcd1b35173f`

`run-cea5b5d2d8ef` passed all five gates on restored PR #23 source/Dockerfile: K=32.576800, T=0.089431 s, M=60,006,400 B, S=647, D=1, points=75.645421. At this run BEST was `run-7cbf51892a7c` (K=32.750840, T=0.088389 s, M=60,166,144 B); the later repeat `run-b2b5c42472eb` is current BEST. The 0.53% K gap is consistent with run variance and the exact solver source is unchanged.

## Official receipt-checkpoint run — `75376b0a3d67c033a4b12d4d950b68b503c4921e`

`run-b2b5c42472eb` passed all five gates on PR #23 source/Dockerfile: K=32.868729, T=0.087625 s, M=60,391,424 B, S=647, D=1. This is **LATEST and new BEST**; K improves 0.36% and T improves 0.86% over `run-7cbf51892a7c` (K=32.750840, T=0.088389 s). Source blobs are unchanged. Retain the PR #22 run as a failed build-flag experiment.

## Developer-main threshold tournament — not transferred to submission

Developer main commit `2f219fb6224d02545d8502b8b11054ed5fd6efa1` records native/pinned GCC15 tournaments on its older source blob `fcd4c4e7` (not the selected submission blob `e11b09e3`). Outputs were exact; threshold 128 regressed seed 1 by 0.18–0.43% and improved seed 7 by only 0.19–0.26%; threshold 192 was mixed/neutral across seeds. The developer rejected all variants. Keep submission PR #23 unchanged; these measurements do not establish a gain on its different source.

## Official latest run — `36ce0278de8128b5ebacad3fd88fc60da4dec86d`

`run-0c111e40947c` passed all five gates on unchanged PR #23 source/Dockerfile: K=32.769415, T=0.088349 s, M=60,063,744 B, S=647, D=1. LATEST; BEST remains `run-b2b5c42472eb` (K=32.868729, T=0.087625 s, M=60,391,424 B), so this run is 0.30% lower in K. PR #23 remains the selected champion; no source change.

## Official latest run — `73c861213ac0e54ce07f817e0e9daa3c51b70d04`

`run-aabd8fda29f6` passed all five gates on unchanged PR #23 source/Dockerfile: K=32.080367, T=0.092306 s, M=59,867,136 B, S=647, D=1. LATEST only; BEST remains `run-b2b5c42472eb` (K=32.868729, T=0.087625 s, M=60,391,424 B). K is 2.40% lower and T 5.34% slower, while M is 524,288 B lower. No code changed, so do not interpret this as a candidate regression.

## Same-source PR #23 repeat summary

Six official runs on unchanged PR #23 source/Dockerfile, all passing all five gates, measured D K values `run-7cbf51892a7c` 32.750840, `run-cea5b5d2d8ef` 32.576800, `run-b2b5c42472eb` 32.868729, `run-0c111e40947c` 32.769415, `run-aabd8fda29f6` 32.080367, and `run-04a9f8f6d4da` 31.540102. Median K=32.663820; range=31.540102–32.868729 (4.07% of median). The last two lower scores are LATEST observations, not code regressions; retain the best verified PR #23 implementation.

## Official latest run — `1a1ebdc1e28bb233773fa663e92886c9fd5e0b26`

`run-04a9f8f6d4da` passed all five gates on unchanged PR #23 source/Dockerfile: K=31.540102, T=0.095212 s, M=60,313,600 B, S=647, D=1. LATEST only; BEST remains `run-b2b5c42472eb` (K=32.868729, T=0.087625 s, M=60,391,424 B). K is 4.04% lower and T 8.67% slower; no code changed.

## Deterministic construction-claim race correction — Nov 2, 2026

- Replaced PR #23's stale-load followed by ordinary atomic store with a relaxed atomic `fetch_or`; append to a region only when the returned prior word did not contain the bit. This makes claims globally unique and keeps each region's construction buffers within their `n`/`m` allocations. Source is PR #24 head `888e22648c0821e5fcdc0963e99dd38be512e496` (`d_traverse.cpp` Git blob `4e45be05890b6228c8df88702da48f51a15fc712`, SHA-256 `d084d2b3574341fdf42a50631679e03e1cdb6bf058feba44313318788b70c006`); the selected source before this fix was `e11b09e...`.
- Independently ran the PR's forced-stale-read and simultaneous-high-degree guard-page reproductions on both old and fixed source at small and full legal dimensions (1,740,512 nodes / 5,000,000 edges). Both old-source runs SIGSEGV; all four fixed-source runs exited successfully and returned the expected distances.
- Fixed source compiled with `g++ -O3 -std=c++17 -pthread -flto -static -s`. It passed 88 differential fixtures (1/4/12 threads × six probe limits), 60 boundary cases, 110 saturation cases, and 30 stress seeds in the developer's independent suite. Exact-source pinned Docker/GCC 15 qualification [41374712573](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41374712573) passed the deterministic repros, fixtures, boundary/saturation/stress suite, six official tiny/sample/full seeds across 4/6/12 workers, and address/undefined plus thread sanitizers. Local Docker cannot start because its storage layer is out of space. Official board evaluation is pending.
- Previous PR #23 board BEST `run-b2b5c42472eb` (K=32.868729) and LATEST `run-04a9f8f6d4da` (K=31.540102) measured the unsafe source. They remain historical receipts only; this correctness defect disqualifies them as champions.

## Official all-track receipt — safe claim-fix commit `4e018992`

`run-92971f1f95cc` passed check/build/correctness/timeout/sandbox on the exact atomic-claim correction: K=31.932285, T=0.092659 s, M=60,686,336 B, S=647, D=1. This is the first safe-source board result and therefore the eligible D BEST/LATEST so far. The numerical feed BEST `run-b2b5c42472eb` remains an unsafe-source historical result and is not a valid correctness champion.

## Official all-track receipt — safe claim-fix commit `4e018992`

`run-92971f1f95cc` passed check/build/correctness/timeout/sandbox on the exact atomic-claim correction: K=31.932285, T=0.092659 s, M=60,686,336 B, S=647, D=1. This is the first safe-source board result and therefore the eligible D BEST/LATEST so far. The numerical feed BEST `run-b2b5c42472eb` remains an unsafe-source historical result and is not a valid correctness champion.


Official all-track receipt — safe claim-fix commit 57bf5df:
run-95260dc5cc5c passed all five gates on the same safe source: K=32.314743, T=0.090606 s, M=60,473,344 B, S=647, D=1. This is the eligible safe-source BEST/LATEST so far; the numerical feed BEST still refers to the disqualified racing source.

## Official rollback verification — commit `701732d`

`run-eac59526a360` passed all five gates on the safe atomic-claim source: K=32.386125, T=0.090460 s, M=60,051,456 B, S=647, D=1. This is the eligible safe-source BEST and LATEST, superseding `run-95260dc5cc5c` (K=32.314743); the higher raw-feed historical score `run-b2b5c42472eb` used the correctness-defective source and remains disqualified.

## Official scored commit `794e8f7` — safe claim source

`run-bbcf25c774ff` passed all five gates: K=32.447889, T=0.090254 s, M=59,822,080 B, S=647, D=1. This is the eligible safe-source BEST and LATEST, superseding `run-eac59526a360` (K=32.386125); the unsafe-source numerical feed BEST remains disqualified.

## Official scored commit `a4b6ed1` — safe claim source

`run-646f14ac127b` passed all five gates: K=32.057046, T=0.092453 s, M=59,846,656 B, S=647, D=1. LATEST; safe-source BEST remains `run-bbcf25c774ff` (K=32.447889). The unsafe-source numerical feed BEST remains disqualified.

## Official scored commit `0b4dcbf` — safe claim source

`run-2e268a627927` passed all five gates: K=32.780740, T=0.088603 s, M=59,531,264 B, S=647, D=1. This is the eligible safe-source BEST/LATEST, superseding `run-bbcf25c774ff` (K=32.447889); the numerical feed BEST remains tied to the disqualified unsafe source.

## Official scored commit `c74c924` — safe claim source

`run-a87f0c9acdce` passed all five gates: K=32.254620, T=0.091414 s, M=59,699,200 B, S=647, D=1. LATEST; eligible safe-source BEST remains `run-2e268a627927` (K=32.780740). The numerical feed BEST still points at the disqualified unsafe source.


## Codex official trial — qualified PR25 byte claims

Trial solver blob `308304cde5e02be22fe33fbce25b9fb5eef9a2cc`, unchanged Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6`, S655/D1. Monotone byte claims prevent within-worker replay; checked recycled-buffer expansion covers inter-worker copies. Full pinned qualification including both deterministic full-size guard regressions passed CI 41374714910. The 189-run local parent-cgroup complete-K matrix is mixed; this trial obtains the actual official hardware result, not a projected improvement.

Safe rollback: PR24 solver `4e45be05890b6228c8df88702da48f51a15fc712`, same Dockerfile, valid BEST `run-2e268a627927`, K32.780740/T0.088603/M59,531,264/S647/D1. Preserve all other tracks. Board result pending; do not promote without comparing valid official receipts.


## Official PR25 result and safe rollback

`run-e696b8644680`, commit `2244048e64033b137daf4bc94242a91069a4b9d1`, passed all five gates: K30.342851, T0.101688 s, M61,517,824 B, S655, D1. The byte-claim architecture loses to valid atomic PR24 BEST K32.780740 (`run-2e268a627927`, T0.088603, M59,531,264, S647/D1). Reject this trial and restore only Track D solver blob `4e45be05890b6228c8df88702da48f51a15fc712` with unchanged Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6`. All other tracks are preserved.

Public competitor leader observed at 04:31 UTC: SweetDreams K34.117253, T0.085564, M57,888,768, S578/D1; our valid BEST is behind by 1.336513 K (4.077% uplift required). The board's numerical HighVelocity BEST still identifies the unsafe PR23 and is not used for selection.


## Official stream-parser trial

Qualified solver `84bfcf0d88933af8f8f87e70e06f6aee543d2881`, original Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6`, S651/D1. Reads three SIMD-mask separators per edge before decoding, preserving PR24 atomic claims and all graph/query algorithms. Full exact pinned qualification passed CI41392615886, including ASan/UBSan, TSan, both forced full-size guard regressions, 88/60/110/stress and organizer restricted-Docker full1/7/17 worker matrices. Local seed1 complete-K ratios at4/6/12 workers are positive but are not official gains; independent full-seed comparison CI41393151550 is running.

Safe rollback remains PR24 solver `4e45be05890b6228c8df88702da48f51a15fc712`, valid BEST K32.780740/run-2e268a627927; latest same-source run-f150bb13a0fa atcommit66a7ed52 measured K32.546058/T0.089478/M60211200/S647/D1. Trial result pending.


## Stream parser first official result — restore valid champion

`run-8b3db1745a15`, commit `f8c35e81ccc211a3ac87768a8b7a71a89667abb2`, passed all five gates: K31.275460/T0.097000/M59,772,928/S651/D1. The independent 306-run pinned comparison CI41393151550 passed every full1/7/17 hash and improved eight of nine median cells locally, but that does not prove official improvement. This run is below valid atomic PR24 BEST K32.780740. Restore Track D solver `4e45be05890b6228c8df88702da48f51a15fc712` while further architectures qualify. Original Dockerfile retained; all other tracks preserved.


## Official frontier/SSE2 trial

Solver `af0e2ac05e7814cca98b100a1e4d1ffc20992efe`, original Dockerfile, S641/D1. One frontier-balanced bidirectional loop removes the separate probe/counters; SSE2 classifies the two possible outgoing edges of bypass vertices. Atomic PR24 ownership and exact saturation/64-bit fallback remain intact. Full qualification CI41395812791 passed pinned restricted Docker references1/7/17 at4/6/12, 88/60/110/stress, both forced full-size guard schedules, ASan/UBSan and TSan; its independent 306-run three-seed paired comparison passed every hash. The separate local parent-cgroup matrix contains225 runs across safe control, candidate, byte degrees and query caps. Official result pending.

Safe rollback: solver `4e45be05890b6228c8df88702da48f51a15fc712`, unchanged Dockerfile, valid BEST K32.780740/run-2e268a627927. Latest restored control run-e3507ded51e6 at23af0eb measured K32.049292/T0.092011/M60641280/S647/D1. No other tracks are changed.


## Frontier/SSE2 result and compact-degree trial

`run-18ef0828aacc`, commit `0f64279be629cbfcff2f166868b6e4ff68d6447a`, passed all gates: K31.934344/T0.093237/M60149760/S641/D1. It does not beat safe PR24 BEST K32.780740; preserve it for matched repeats, not promotion from local timings alone.

Next qualified trial: compact degrees, solver `4025847191c1022a70503c185311c648edb9c028`, original Dockerfile, S664/D1. Exact overflow escapes preserve arbitrary legal degrees. `mremap` shrinking is checked; atomic claims remain globally unique. Full qualification and independent three-seed comparison passed CI41395815104. Local225-run complete-K matrix improved8/9 cells for byte degrees (diagnostic geometric-mean ratio1.0192); official improvement is unproven. Rollback remains PR24 solver `4e45be05890b6228c8df88702da48f51a15fc712`, original Dockerfile, valid BEST run-2e268a627927. Other tracks unchanged.


## Compact-degree result and eight-query-worker trial

`run-e6a3048b86cd`, commit `f0fc43c0e3ea8844e851a39642a485364e8710c5`, passed every gate: K30.369166/T0.103164/M58482688/S664/D1. This first result does not beat safe PR24 BEST K32.780740. Do not promote from the local memory gain alone.

Next qualified variant limits queries to eight workers while construction keeps the configured count: solver `35569da8c7458df743a4a5f64834cb654bd47497`, original Dockerfile, S664/D1, exact-source qualification CI41397966495 passed all mandatory reference, sanitizer, adversarial and sandbox gates. Its local225-run matrix was positive8/9 cells (geometric-mean K ratio1.02034 against PR24 across separate local configurations; not an official projection). Evaluate the actual six-physical-core result before selection. Safe rollback remains solver `4e45be05890b6228c8df88702da48f51a15fc712` / Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6`, valid BEST run-2e268a627927. Other tracks unchanged.


## Eight-query-worker result and matched safe control

`run-c0fd6e318ce4`, commit `9af49acdea4d27da73263a7e49d4524107c537c6`, passed all gates: K32.408480/T0.091973/M56307712/S664/D1. Eight query workers substantially recover the preceding compact-degree trial's runtime and lower its memory, but this first result remains below valid PR24 BEST K32.780740. Restore safe solver `4e45be05890b6228c8df88702da48f51a15fc712` with unchanged Dockerfile for a matched control before judging another repeat. Preserve PR29 as a qualified alternative. Six-query-worker and phase-specific six-growth-worker variants are qualifying independently; no official improvement is claimed. A/B/C unchanged.


## Qualified six-query-worker trial

Solver `038e25ac5d2b90e2e2db52b130f1acd1fb1c6795`, original Dockerfile, S664/D1. Only the compact-degree variant's query cap changes8 to6; parsing/growth/CSR keep up to12 workers. Exact-source qualification CI41402547668 passed all mandatory sanitizer, forced-full-size guard, differential/boundary/saturation/stress and restricted-Docker reference gates. Local full1/7/17 parent-cgroup comparisons are preserved in research receipts. This tests the actual six-physical-core scorer rather than extrapolating from local quotas.

Previous cap8 run-c0fd6e318ce4 measured K32.408480/T0.091973/M56307712/S664/D1. Official restored control atf71d444/run-26d8e5a4fb1d measured K31.759092/T0.094263/M59740160/S647/D1. The valid champion remains PR24 K32.780740/run-2e268a627927, solver `4e45be05890b6228c8df88702da48f51a15fc712`. Preserve that exact rollback. A/B/C and shared configuration are unchanged.


## Six-query-worker observation and bounded-queue trial

Exact compact-degree six-query-worker source `038e25ac5d2b90e2e2db52b130f1acd1fb1c6795` passed all official gates in run-14d33bcc113a atcommit777ef7d8: K31.395680/T0.098678/M55349248/S664/D1. Compare source blobs rather than only the metadata commit. Valid historical BEST remains PR24 K32.780740; no promotion is claimed.

Next fully qualified candidate: solver `98464939ea3971f366fdb08bcc927fde72051457`, original Dockerfile, narrow queues specialized for exact keys below65535 while 64-bit fallback keeps the general queue. Global atomic claims and frontier/SSE2 architecture are preserved. CI41402876536 passed all qualification jobs and independent full1/7/17 matched comparisons. Local native timing is promising but not an official gain. Preserve exact PR24 solver `4e45be05890b6228c8df88702da48f51a15fc712` / Dockerfile `8eabe09b96a60131ce5bfda3f098011e1f0863e6` for rollback. A/B/C unchanged.
