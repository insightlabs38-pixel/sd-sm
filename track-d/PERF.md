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
