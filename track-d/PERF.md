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

