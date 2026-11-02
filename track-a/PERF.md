# Track A performance log

## Exact C++ baseline, October 30, 2026

- Design: mmap parse, full-byte endpoint interning, count/scatter, exact local sorting or multiselect.
- Compiler: GCC 14.2, `-O3 -std=c++20 -static-libstdc++ -static-libgcc`.
- Local differential tests: 12 cases, empty through 310,000 records, four seeds, uint32 extremes, duplicates, statuses, boundaries, bytewise endpoint order. All passed against Python oracle.
- Official worked example: byte-exact locally. Official seed-1 and unseen-seed hashes await GitHub CI.
- Initial 310,000-record synthetic run: 0.05 s wall, 36,544 KiB peak RSS, local development container only.

## Local full-size synthetic comparisons

- Generated 3,100,000 legal-format lines (~204 MiB) with a Zipf-skewed endpoint distribution. This is **not** the official dataset or scoring hardware.
- 20 randomized-order, single-core pinned trials: initial unordered-map baseline median 0.3103 s, exact full-key flat hash table median 0.2645 s. Variance and cross-run contention remain significant.
- Sorting/selection threshold 256 is an additional local candidate; performance varied within host noise. All 12 synthetic differential cases passed after combining it with the flat table.
- Two-pass direct scatter challenger measured 0.4944 s median versus 0.3252 s one-pass on 12 local trials; rejected for now.
- No official board run ID exists yet. Luna records actual board IDs after verified integration.

## Luna integration validation, October 30, 2026

- Promoted candidate source: `sd-ta` HEAD `a0dc2f45b6cc57421a5afae6f3c0dc7000621be3`; prior official Track A is retained in parent commit `8eb291667c6745b310689ebf0f68034278bcef1f` for rollback.
- All 12 developer synthetic differential tests passed. Organizer reference matched on official seed-1 full data (SHA-256 `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3`, also the published hash) and seed-42 sample (SHA-256 `835c36377118af19264750c9b1031225ead44a8555e913c22d31a827dbe486c8`).
- Offline allowlisted Docker build passed; image size 79 MB. Full-data sandbox check produced exactly `summary.txt` with the expected hash. This local container run took 1.42 s including startup.
- Twelve alternating single-core local runs on full seed-1: previous official binary median 0.4228 s; new binary median 0.3973 s (+6.4% speed). Local cgroup peak memory samples were 40,443,904 and 40,591,360 bytes respectively. These measurements are not scoring-box results.
- Board run IDs: none. The official repo is not present in the live board registry yet; no official score claimed.

## Parallel parsing handoff validation, October 30, 2026

- Promoted developer HEAD `e94671135adfebf4802343412306140cd57360bb`; previous integrated flat-table champion remains in parent commit `d001f5dccf26807b83bb40e74fa7af182bb47eff` for rollback.
- The four parse workers and three percentile-output workers pass the official full seed-1 hash `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3` and the seed-42 sample hash `835c36377118af19264750c9b1031225ead44a8555e913c22d31a827dbe486c8` in the board-equivalent sandbox. Full invocation took 2.18 s including container startup; sample invocation took 2.01 s. These local timings are not board measurements.
- Developer randomized 20-run synthetic medians: one-thread flat/scatter 0.2604 s; parse+output parallel 0.1171 s (~55% lower). The 204 MiB synthetic dataset is not official input or scoring hardware. Developer-reported parallel peak RSS was ~253,748 KiB.
- Offline allowlisted Docker build passed; image size 79 MB. No live board run ID exists; no board score is claimed.

## Verified parallel-scatter promotion, October 30, 2026

- Promoted `sd-ta` main HEAD `a877750cb57c3ea59307f1d54e4dcb4647475fc2`, source after the prior official A champion `e946711`; parent history retains that candidate for rollback.
- Independent native checks matched the organizer full seed-1 SHA-256 `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3` and sample seed-42 SHA-256 `835c36377118af19264750c9b1031225ead44a8555e913c22d31a827dbe486c8`.
- GitHub Actions run [41087414448](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41087414448) passed tiny/sample/full seed-1, sample seed-2, the allowlist check and the offline Docker sandbox. The same CI commit is `a877750`.
- Developer synthetic measurements: parallel scatter with three output workers 0.1223 s vs prior sequential scatter 0.1321 s; four output workers measured 0.1082 s vs three at 0.1134 s on that host. These are synthetic/local, not board timings.
- No official board run ID or score is claimed.


## Five-worker parser and bounded delimiter scan, October 30, 2026

- Promoted `sd-ta` main HEAD `704958d60f9f16a4d97ff01d0f676644bee78172`, source blob `0b775cab4d0c6525d676fd0d8ef5340656027fcc`. The prior official A candidate remains in parent release commit `fb2e1fc` for rollback.
- Five parser workers beat four on the developer's 4-CPU-quota host across three synthetic full-size distributions. Reported medians: uniform endpoints 0.09064 s vs 0.09550 s (about 5.1% faster); Zipf-skewed 0.08265 s vs 0.08920 s (about 7.3% faster). A fifth worker adds about 1.6 MiB of group metadata. Synthetic measurements are not official scoring results.
- Latest GitHub Actions run [41096594772](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41096594772) passed tiny/sample/full seed-1 exactness, sample seed 2, allowlist validation and offline restricted Docker execution on the exact current HEAD.
- No official board run ID or K score is claimed.

## Sampled endpoint hash promotion, October 30, 2026

- Candidate `sd-ta` main HEAD `5b98bcee29a6e9e51149edc5c36665a74990e9ea`, source blob `b2afeeeda365791bfefae00ad4cd0c4653471a4c`; rollback is this release's parent Track A source (`00838f7`).
- GitHub Actions [41105415380](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41105415380) passed tiny/sample/full seed-1 hashes, seed-2 differential, allowlist validation and restricted offline Docker. Full output SHA-256: `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3`.
- Seven-run full-input paired median versus the selection-equivalent `47e3db0` source: 0.132078 s to 0.120100 s (9.1% lower). This is a developer CI runner measurement, not scoring hardware. No official board run ID or score is available.

## CRC endpoint fingerprint and compact parser state, October 30, 2026

- Candidate: `sd-ta` main HEAD `2ce5a1fc4a46e78106ac9bf80d6218bebc07ad5b`, source blob `5b60b456af12216116149afab37869fb64daada9`. Previous official release `1c235c35cc93ea146cf794254eecd56fab8f9948` remains the rollback point.
- Current-head CI [41112488117](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41112488117) passed synthetic differential cases, official seed-1 tiny/sample/full hashes, sample seed 2 against the reference, Docker allowlist, offline build and restricted Docker tiny execution. Full output SHA-256: `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3`.
- On this local three-CPU host, ten interleaved full seed-1 runs of the previous official source and candidate both matched that hash. Median runtime fell from 0.3185 s to 0.2859 s (10.2%); sampled process VmHWM fell from 283,052 to 280,480 KiB (0.9%). This is local evidence, not scoring-box T/M.
- A separate seven-run CI comparison on current code versus CRC predecessor `8c754fc` measured 0.092090 s to 0.091419 s (0.7%); runner timing only. The candidate adds one physical source line, uses CRC32 only as a fingerprint, and retains exact full-byte equality. No runtime dependency was added.
- Official board BEST/LATEST: unavailable; the team has no registration entry and no board run IDs exist. No official score is claimed.

## Integrator qualification: compact fingerprints and packed worker groups (October 30, 2026)

- Imported developer `sd-ta` commit `7e5ee07a69a79673caeb779c1d2c0ac0b28d0d2a`, source blob `1878916aae2fe295387899b9b0522f777aacdc71`. Previous official champion is recoverable from submission commit `34dee9b16ab17362b12e75289151a0a9750b2cb8` (source SHA-256 `6933358b689202d3f0e4d0abd79c5c85ec3510316a171609b6210fc613ab822d`).
- GitHub Actions `41120735228` passed current-head exactness, adversarial CRC-alias tests, Docker allowlist and offline container full-output validation. Earlier paired full seed-1 run `41120372612` measured 13-run median 0.105081 s before packed local keys and 0.103475 s after (1.5% lower); all official hashes and synthetic oracle passed. This is runner-local evidence, not a board score; timing gain is small and may be within noise.
- BEST/LATEST official board result: none (repository/team not present in board feed at this integration); no board run ID or score is claimed. Prior verified source remains available at the parent checkpoint.

## Champion reconciliation — October 30, 2026

- Restored the source/build/docs from board-best commit `34dee9b` (source blob `5b60b456af12216116149afab37869fb64daada9`) after the latest official run at `647f752` measured K=21.074231 versus the actual best K=21.532045 at `34dee9b`. The repeated score is the deciding evidence; the earlier local CRC/packing comparisons remain runner-only.
- Developer `main` HEAD `624fcec` passed current-head exactness and restricted Docker in CI [41136084173]. Its 13-run local median was 0.111769 s before and 0.111210 s after (0.5% lower), with no peak-memory measurement; the candidate adds 25 physical source lines over the integrated code. Its estimated net K is not positive after source-size cost and unknown memory, so it remains unpromoted.

## Official board receipts — raw-feed snapshot 2026-10-30 22:52:25 UTC

HighVelocity (`highvelocity-7f330e`) is registered. The watcher reported submission HEAD `3059e71b54cd02e920e995d186a369b4be9c0aeb`, healthy, with no queued or in-flight run at this snapshot. BEST and LATEST are both this successful live-board run; build, check, correctness, sandbox, and timeout gates all passed. These are board IDs, not CI IDs. Earlier “no board run/registration” notes are historical and superseded here.

- **BEST:** `run-52a21f98657c`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.073125 s, M=50,302,976 bytes, S=325, D=1, K=21.755557, points=66.878511.
- **LATEST:** `run-52a21f98657c`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.073125 s, M=50,302,976 bytes, S=325, D=1, K=21.755557, points=66.878511.


## Official board receipts — raw-feed snapshot 2026-10-30 22:58:54 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher was healthy at `40847ba5fde8714895533f7b47ce8fee48baa09e`, and the dispatch queue was idle after scoring. All five gates (build, check, correctness, sandbox, timeout) passed; failure was null. BEST and LATEST below are the board's records at this snapshot. These board run IDs are distinct from GitHub Actions IDs.

- **BEST:** `run-52a21f98657c`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=0.073125 s, M=50,302,976 bytes, S=325, D=1, K=21.755557, points=66.878511.
- **LATEST:** `run-bc89bd32b183`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=0.074765 s, M=49,328,128 bytes, S=325, D=1, K=21.600002, points=66.722690.


## Official board results — raw-feed snapshot 2026-10-30 23:10:48 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. The watcher was healthy at `01d4852e1271d5bec3d6de9aaa7641f8616730cb` with an idle queue. Both records passed build, check, correctness, sandbox, and timeout gates; failure was null. These are live-board measurements; BEST and LATEST are separately reported, and run IDs are not GitHub Actions IDs.

- **BEST:** `run-c25251fd5cdb`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.072742 s, M=50,122,752 bytes, S=325, D=1, K=21.828419, points=66.951114.
- **LATEST:** `run-c25251fd5cdb`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.072742 s, M=50,122,752 bytes, S=325, D=1, K=21.828419, points=66.951114.


## Rejected developer candidate — `sd-ta` `5542976336d1f088973ff7a09a85d83bd977bd9b`

- Current-head CI [41142583488](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41142583488) passed exactness and restricted offline Docker; the full seed-1 reference hash matched. CI paired medians against its developer champion were 0.084978 s to 0.085132 s (candidate 0.18% slower).
- Integrator paired 13-run local full seed-1 trials against official source scored at `01d4852`: median T 0.296801 s to 0.304545 s (candidate 2.61% slower); sampled median RSS 287,211,520 to 287,608,832 bytes (+0.14%). All output hashes matched. These are local measurements, not board T/M.
- Candidate reduces source code by six counted nonblank lines in the track source; with D unchanged at 1 and the measured T/M ratios, the approximate K ratio is 0.990 (about K=21.60 versus board BEST 21.828 at `run-c25251fd5cdb`). Exact scc S was not measured for the candidate, so this is an estimate. Not promoted; the scored A champion remains unchanged.


## Official board results — raw-feed snapshot 2026-10-31 00:12:03 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. Watcher was healthy at `157f1d478136fd0d7950aa2a82e121c087ec7ec7`, with no queued or in-flight run. Every gate passed; failure was null. These are board measurements, and BEST/LATEST are tracked separately. Board run IDs are not GitHub Actions IDs.

- **BEST:** `run-c25251fd5cdb`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.072742 s, M=50,122,752 bytes, S=325, D=1, K=21.828419, points=66.951114.
- **LATEST:** `run-9afdeb98f26b`; commit `157f1d478136fd0d7950aa2a82e121c087ec7ec7`; T=0.075135 s, M=49,733,632 bytes, S=325, D=1, K=21.511501, points=66.633535.


## Official board results — raw-feed snapshot 2026-10-31 00:17:27 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`, queue idle. All five gates passed and failure was null. BEST and LATEST are reported separately; these are live-board IDs, not GitHub Actions IDs.

- **BEST:** `run-c25251fd5cdb`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=0.072742 s, M=50,122,752 bytes, S=325, D=1, K=21.828419, points=66.951114.
- **LATEST:** `run-059bcd1867c7`; commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.073655 s, M=49,848,320 bytes, S=325, D=1, K=21.716542, points=66.839533.


## Verified `sd-ta` main candidate evaluated against the official source — October 31, 2026

- Imported from developer HEAD `59a73a7c2d85d3f396313de528defafb82465572`, source blob `71fb370c88f6a5423898ad63ae7e3c644ca89444`; rollback is parent commit `b8e6540`. CI [41148649319](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41148649319) passed exactness and restricted offline Docker on this source. A separate paired 13-run full seed-1 local comparison against the then-official source matched the published hash each run: T median 0.232623 to 0.227738 s (2.1% lower), sampled RSS 287,203,328 to 281,677,824 bytes (1.9% lower). These are local, not board measurements.
- Pinned clang-format 23.1.3 and scc 4.1.0 gave S=325 for the scored source and S=321 for the candidate; D remains 1. Applying the paired local T/M ratios and exact S delta to board BEST K=21.828419 gives estimated K≈22.19 (+1.6%). The estimate is not a board result; actual scoring at `run-d9a6b26a1de8` recorded T=0.067238 s, M=44,072,960 bytes, S=321, K=23.339245 (BEST); see the latest raw-feed receipt below.


## Official board results — raw feed, 2026-10-31 00:23:55 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `73d8cecee9e50825a4f416b77c11fec448955782`; queue idle. All five gates passed for BEST and LATEST; failure was null.

- **BEST = LATEST:** `run-d9a6b26a1de8`, commit `73d8cecee9e50825a4f416b77c11fec448955782`; T=0.067238 s, M=44,072,960 bytes, S=321, D=1, K=23.339245, points=68.404340. New BEST.


## Official board results — raw feed observed 2026-10-31 00:29:07 UTC

Watcher was healthy at `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca` (last checked 00:28:14 UTC); queue idle. All five gates passed; failure was null.

- **BEST:** `run-d9a6b26a1de8`, commit `73d8cecee9e50825a4f416b77c11fec448955782`; T=0.067238 s, M=44,072,960 bytes, S=321, D=1, K=23.339245, points=68.404340.
- **LATEST:** `run-f8862173d0fd`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.069971 s, M=43,937,792 bytes, S=321, D=1, K=22.892960, points=67.985098.


## Official board results — raw feed observed 2026-10-31 00:34:36 UTC

Watcher healthy at `8233a6406105e8580d72bc059d91e48eb88e0868`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST = LATEST:** `run-12d646b0e089`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.066496 s, M=44,417,024 bytes, S=321, D=1, K=23.432627, points=68.491049.


## Official board results — raw feed observed 2026-10-31 00:40:29 UTC

Watcher healthy at `b6f184e81a93554f4dd2b2e0284258345964f45f`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST = LATEST:** `run-a0046ba13a37`, commit `b6f184e81a93554f4dd2b2e0284258345964f45f`; T=0.066189 s, M=44,433,408 bytes, S=321, D=1, K=23.485175, points=68.539690. New BEST.


## Official board results — raw feed observed 2026-10-31 00:46:16 UTC

Watcher healthy at `94a98da3f2e1de31f3b6fc308194c698f3603249`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-a0046ba13a37`, commit `b6f184e81a93554f4dd2b2e0284258345964f45f`; T=0.066189 s, M=44,433,408 bytes, S=321, D=1, K=23.485175, points=68.539690.
- **LATEST:** `run-c807bc65e77a`, commit `94a98da3f2e1de31f3b6fc308194c698f3603249`; T=0.074522 s, M=44,417,024 bytes, S=321, D=1, K=22.134846, points=67.253825.


## Official board results — raw feed observed 2026-10-31 00:51:41 UTC

Watcher healthy at `8b137acc1b2f3a83c9b7c422088b7b966357232e`, queue idle; all five gates passed for every latest run, failure null.

- **BEST = LATEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912. New BEST.


## Official board results — raw feed observed 2026-10-31 01:14:45 UTC

Watcher healthy at `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-2abb02ab5f35`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.067389 s, M=44,273,664 bytes, S=321, D=1, K=23.291907, points=68.360252.


## Fixed-span UTC hour-index candidate — developer CI, 2026-10-31

Developer `sd-ta/main` commit `65f158ae8b817bc36f547c53b77333ce07c4fcec` simplifies the frozen 72-hour date mapping. CI run [41154124123](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41154124123) passed official seed-1 tiny/sample/full hashes, synthetic and seed-2/3 sample differentials, Docker allowlist/offline sandbox, and scored-style cgroup checks for the developer main candidate. Its full-branch 13-pair seed-1 medians were 0.113791 s (prior) vs 0.113456 s (candidate), ratio 0.9971; RSS 275,748 vs 275,668 KiB; cgroup peak 44,138,496 vs 43,798,528 bytes. These paired numbers include the developer main candidate’s other changes and do not isolate the date-index edit. The imported date-index change scored below the known-good A candidate on official run `run-4fc2b3bedf5d`; it is rolled back in the latest integration commit.


## Later developer-main candidate review

The follow-up `sd-ta/main` commit `388406ca0dcd93516dc292fc2cbe2789c599ff5d` separated parse and group counting. Its CI run [41154503918](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41154503918) passed exactness and Docker checks, but the 13-pair full seed-1 median was 0.108288 s (parent) vs 0.108528 s (candidate, ratio 1.0022); RSS was 275,748 vs 275,844 KiB and cgroup peak 43,827,200 vs 43,864,064 bytes. The slight regression and added operations do not support promotion; only the prior fixed-span index edit is imported.


## Official latest board results — raw feed observed 2026-10-31 01:19:37 UTC

Watcher healthy at `266578e73fec11894c067b8b11a0910657a8ccff`, queue idle; all five gates passed for all four tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-4fc2b3bedf5d`, commit `266578e73fec11894c067b8b11a0910657a8ccff`; T=0.070131 s, M=44,830,720 bytes, S=320, D=1, K=22.785667, points=67.883087.

The fixed-span UTC indexing challenger regressed on the official board; it is rolled back in the next commit. Retain `8b137ac` as the known-good A source.

## Later developer-main fusion candidate review

`sd-ta/main` commit `4f39ecbf78b97158510863d8d11528fc333abb9e` fused group reconciliation with scatter offset preparation. CI [41154977773](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41154977773) passed exactness and Docker gates. Its 13-pair full seed-1 comparison measured 0.086840 s (prior) vs 0.087112 s (candidate, ratio 1.0031); RSS was 275,984 vs 275,960 KiB and cgroup peak 43,827,200 vs 44,097,536 bytes. The measured time and cgroup memory regress, so this developer-main candidate is not promoted.


## Official board results — raw feed observed 2026-10-31 01:25:23 UTC

Watcher healthy at `09ee42d8656b9b599401140eb38d5d76b07a7566`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-c05c5ce42264`, commit `09ee42d8656b9b599401140eb38d5d76b07a7566`; T=0.067342 s, M=45,178,880 bytes, S=321, D=1, K=23.205907, points=68.279927.


## Official board results — raw feed observed 2026-10-31 01:31:36 UTC

Watcher healthy at `ed14252dd1ed2a882887dffd6bb61950f03a1c85`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-095ad1c1c33a`, commit `ed14252dd1ed2a882887dffd6bb61950f03a1c85`; T=0.075741 s, M=43,905,024 bytes, S=321, D=1, K=22.006971, points=67.128014.


## Official board results — raw feed observed 2026-10-31 01:36:50 UTC

Watcher healthy at `03742f51c5f91e7313584860fb6de63ad83fbae4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-e90442236c9c`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.070293 s, M=44,027,904 bytes, S=321, D=1, K=22.831109, points=67.926350.


## Official board latest snapshot — raw feed observed 2026-10-31 01:42:00 UTC

Watcher healthy at `3077ed42f746f6ed84d122899e611b5af3dac0e4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-d72de665e1ba`, commit `3077ed42f746f6ed84d122899e611b5af3dac0e4`; T=0.067168 s, M=44,642,304 bytes, S=321, D=1, K=23.291535, points=68.359906.

## Official board results — raw feed observed 2026-10-31 01:50:28 UTC

Watcher healthy at `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`, queue idle. All five gates passed for all four tracks; failures were null.

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-aaa0e3a92619`, commit `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`; T=0.070241 s, M=44,568,576 bytes, S=321, D=1, K=22.783873, points=67.881377.

## Official rollback snapshot — raw feed 2026-10-31 01:55 UTC

`run-198d00179847` scored commit `4567e5529f0418efdd26c132701f1bf296bcb49d`; all five gates passed, failure null. **LATEST:** T=0.070336 s, M=44,290,048 bytes, S=321, D=1, K=22.797046, points=67.893929. **BEST:** `run-925ee63e320b`, K=23.500561, points=68.553912.

## Official board snapshot — raw feed 2026-10-31 02:00:12 UTC

Watcher healthy at `6bf7383dc5439ccd0768435c1932c243e16c0584`, queue idle. All five gates passed, failure null. **BEST:** `run-925ee63e320b`, K=23.500561, points=68.553912. **LATEST:** `run-7f0063baa55f`, T=0.070014 s, M=44,822,528 bytes, S=321, D=1, K=22.794860, points=67.891846.


## Official board results — raw feed observed 2026-10-31 03:05:10 UTC

The watcher was healthy at commit `b453c295cdbca2e3c740d71d6c35e57b8dec3662`. Run `run-a5130b6c012d` on this commit passed build, check, correctness, timeout and sandbox gates. LATEST: T=0.066859 s, M=44,302,336 bytes, S=321, D=1, K=23.381016, points=68.443169. BEST remains `run-925ee63e320b`: T=0.066078 s, M=44,474,368 bytes, S=321, D=1, K=23.500561, points=68.553912. This run did not replace BEST; retain the current source and track rollback history.


## Board baseline before multi-track trial — raw S3 feed 2026-10-31 03:49:18 UTC

- **BEST:** `run-925ee63e320b`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.066078 s, M=44,474,368 B, S=321, D=1, K=23.500561, points=68.553912.
- **LATEST:** `run-0f01aae00b82`, official HEAD `a30276e460e00aa279aa41cca913a10a90a1a6a8`; T=0.069630 s, M=43,933,696 B, S=321, D=1, K=22.949377, points=68.038545. All five gates passed.

## A candidate board trial — run `run-2eaed1646568`

- Scored commit `f91d9c075066881eb480cd7d27a9f33bfdc43350`; build, check, correctness, timeout and sandbox gates all passed. T=0.065495 s, M=44,552,192 B, S=319, D=1, K=23.618804, points=68.662895.
- Against prior BEST `run-925ee63e320b` (T=0.066078 s, M=44,474,368 B, S=321, K=23.500561), K improved 0.50%, T improved 0.88%, and measured S fell by 2. A source trial is therefore promoted; parent source remains the rollback checkpoint.


## Official baseline before Track B hybrid trial — raw feed 2026-10-31 04:14 UTC

On official HEAD `ec1140f4d0bd607a02b9fae4be61ce5fe3bae986`, latest run `run-d53d14fca94c` passed all five gates: T=0.065558 s, M=43,933,696 B, S=319, D=1, K=23.673550, points=68.713170. BEST is the same run. The baseline precedes the controlled Track B trial.


## Official board results after Track B trial — raw feed 2026-10-31 04:17:53 UTC

HighVelocity watcher healthy at `a2f99921eaf302381af4fa63e6b131588c3fb572`; `run-5a28f49a0787` passed all five gates. **LATEST:** T=0.070086 s, M=43,745,280 B, S=319, D=1, K=22.915742, points=68.006696. **BEST:** `run-d53d14fca94c`, K=23.673550, points=68.713170.


## Controlled packed-tuple trial prepared — 2026-10-31

- Candidate imported from `sd-ta/main` HEAD `0c861331cf8ac4493d1e848a8c459cb8209db789`; source uses a 24-bit group/error field plus full 32-bit latency, with compile-time 7-byte size check. Current official source remains recoverable from parent commit `a62ff8d662a8f342256a53b20e05a3e2a9af6231`.
- Qualification [CI 41167517902](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41167517902) passed published seed-1 hashes, seed-2/3 sample differential, synthetic oracle, and restricted offline Docker. Thirteen-run paired seed-1 comparison: group-first 0.111273 s, x86-64-v3 champion 0.110813 s; charged cgroup peak 40,919,040 B vs 44,109,824 B. Estimated K +1.25% from T/M/S/D; this is a CI estimate, not an official result.
- The two packed field layouts were effectively tied; group-first was retained. Six-byte sparse overflow and reserve-slack experiments were rejected. Official board result pending; no run ID or score claimed.


## Official board snapshot — 2026-10-31 04:21:29 UTC

HighVelocity (`highvelocity-7f330e`) watcher was healthy at official HEAD `a62ff8d662a8f342256a53b20e05a3e2a9af6231`; queue clear. All five gates passed.

- **BEST = LATEST:** `run-34af1c8a1977`; T=0.065349 s, M=44,040,192 B, S=319, D=1, K=23.699898, points=68.737324. New BEST versus `run-d53d14fca94c` (K=23.673550).


## Official board snapshot — 2026-10-31 04:25:59 UTC

- **BEST = LATEST:** `run-aad4ae1ad447` on `6ce631e9aed748609f3fbd289ec599cb4abf152d`; all five gates passed. T=0.065900 s, M=41,218,048 B, S=321, D=1, K=23.892877, points=68.913422. K is up 0.81% from previous BEST `run-34af1c8a1977` (23.699898); the packed-tuple trial is promoted.


## Official board snapshot — 2026-10-31 04:30:35 UTC

HighVelocity was registered and the watcher was healthy; all five gates passed for the scored submission.

- **BEST:** `run-aad4ae1ad447`; T=0.065900 s, M=41,218,048 B, S=321, D=1, K=23.892877, points=68.913422.
- **LATEST:** `run-13f944646ef2` on `952084e36d4a8309c21c175f7208a40fe40c2702`; T=0.066082 s, M=41,250,816 B, S=321, D=1, K=23.856160, points=68.880027.

## Controlled endpoint-hash and AVX2 candidate prepared — 2026-10-31

- Imported `sd-ta/main` HEAD `3bd56063faa081e6dfef77afeb99044ede01dfe5`, source blob `e0c5e2fbbf9baebe5af62aa79feacfd24d94f8d2`; rollback remains in parent `952084e36d4a8309c21c175f7208a40fe40c2702`.
- CI `41174690609`, `41175038825`, and `41175190484` passed published hashes, holdout differentials, synthetic oracle, edge sanitizers, Docker allowlist and offline execution. Final 31-run paired full-seed medians: sparse 0.085658 s vs AVX2 0.083057 s; cgroup peaks 41,553,920 vs 41,005,056 B. Around ten extra counted lines; estimated +1.2–1.3% K versus sparse, not an official score.
- Official board result pending; no run ID or score claimed.


## Official board snapshot and rejected AVX2 trial — 2026-10-31 06:18:39 UTC

- **BEST:** `run-aad4ae1ad447`; T=0.065900 s, M=41,218,048 B, S=321, D=1, K=23.892877, points=68.913422.
- **LATEST:** `run-51141caaeccd` on `bd1e696b8a738a9f6d52c2faa16d9a6244c64d5e`; all five gates passed. AVX2 candidate T=0.067907 s, M=41,631,744 B, S=337, D=1, K=23.319418, points=68.385886. Against BEST, K fell 2.40%, time rose 3.05%, memory rose about 1.0%, and S rose by 16. Candidate rejected; packed source restored from parent `952084e36d4a8309c21c175f7208a40fe40c2702`.


## Official board snapshot — 2026-10-31 06:23:31 UTC

- **BEST:** `run-aad4ae1ad447`; T=0.065900 s, M=41,218,048 B, S=321, D=1, K=23.892877, points=68.913422.
- **LATEST:** `run-5b4376b4939e` on `8e70985f8a07fc6b5adaa9435c4d6b83638a2665`; all five gates passed. T=0.070456 s, M=41,459,712 B, S=321, D=1, K=23.080456, points=68.162220.

## Official board receipt — 2026-10-31 06:59:47 UTC

- Run `run-c9a49ee2057b` scored commit `f3bd76617870c71c81594817b54ad366113718bc`; all five gates passed. LATEST: T=0.069081 s, M=41,443,328 B, S=321, D=1, K=23.310866, points=68.377920. BEST remains `run-aad4ae1ad447`: K=23.892877. This receipt is 2.436% below BEST; no Track A source change was included.

## Six-byte staged records official trial — October 31, 2026

- Candidate source blob `0034dba9d60573da24b65512f8b20e17bf50aa9e` from `sd-ta/main` HEAD `4e08e9d8cf0cb7500f144097bb063940b18d646c`. It stages each record as a six-byte local endpoint ID plus full 32-bit latency and records hour runs separately. The official Dockerfile is byte-identical to the repository Dockerfile.
- Exact-source CI [41179012512](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41179012512) passed synthetic differential tests, official seed-1 tiny/sample/full hashes, seed-2/3 sample differential, the Docker allowlist/offline sandbox, and scored-style cgroup memory checks. Thirty-one full-seed-1 measurements: 0.103128 s versus 0.109233 s for the verified v3 champion (ratio 0.9441). Cgroup peak was 39,510,016 B versus 41,299,968 B. These are CI runner measurements, not board T/M/K. A local native build and 12 synthetic differential cases also passed.
- Previous official A BEST remains `run-aad4ae1ad447` (K=23.892877). The AVX-only predecessor regressed on its earlier official trial; this is a fresh trial of the added six-byte staging change, not a promotion claim. Parent commit retains the prior official source for rollback. The official run below did not promote this candidate; the known-good source has been restored.

## Official board snapshot — 2026-10-31 07:06:34 UTC

- `run-d5429d5182ce` scored `281c60f59cbe6c6a8c51f77aba7daad102151abd`; all five gates passed. LATEST: T=0.069235 s, M=41,095,168 B, S=321, D=1, K=23.324247. BEST remains `run-aad4ae1ad447` (K=23.892877); no A source change was present in that snapshot.

## Six-byte staging official trial — rejected, 2026-10-31

- Board run `run-9243aef5cd8c` scored `aa84dc52fefa309db4dbc5c2b9aefc07863ea13a`; all five gates passed. Candidate LATEST: T=0.065933 s, M=39,358,464 B, S=357, D=1, K=23.727125, points=68.762256. BEST remains `run-aad4ae1ad447`, K=23.892877. K was 0.694% below BEST despite 4.5% lower memory and nearly unchanged T; the extra source cost outweighed those gains. Restored source blob `1d59a36e5166f19cbf870f6458da5179f17bf1ed` from parent `281c60f`.

## Official board snapshot — 2026-10-31 07:12:34 UTC

- Same actual receipt: `run-9243aef5cd8c` on `aa84dc52fefa309db4dbc5c2b9aefc07863ea13a`; all gates passed. This is the latest scored A source trial; current branch has the known-good rollback source while its new score is pending.

## Official board snapshot — 2026-10-31 07:17:07 UTC

- `run-29c6b4ffe48d` scored exact rollback HEAD `15cc7c6f38a26d0f3515727d6d217ba4d95094b9`; all five gates passed. LATEST: T=0.068730 s, M=41,545,728 B, S=321, D=1, K=23.358782, points=68.422510. BEST remains `run-aad4ae1ad447` (K=23.892877); this is the verified known-good source, with ordinary run variance below BEST.


## Official board snapshot — 2026-10-31 12:11:52 UTC

- **BEST:** `run-aad4ae1ad447`, T=0.065900 s, M=41,218,048 B, S=321, D=1, K=23.892877, points=68.913422.
- **LATEST:** `run-e1cee7520ae4` on `2b5afc9408dcd202ca3f113e100d02fc673d04ee`; all five gates passed. T=0.068997 s, M=41,402,368 B, S=321, D=1, K=23.329665, points=68.395425.
- Candidate trial source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is from `sd-ta/main` source at HEAD `765ed40783a534e3f5ae5f412ed9483000bd63a9` (latest source-changing ancestor `d9680bd`). Exact-source qualification CI `41183532479` passed. Candidate board result is pending; parent commit retains the known-good source for rollback.


## Official candidate result — 2026-10-31 12:15:45 UTC

- Board run `run-383d474cf6f7` scored `187269afc6efbeee7ac01b4f623f7c7f049ea44b`; all five gates passed. **LATEST and new BEST:** T=0.022463 s, M=20,987,904 B, S=442, D=1, K=44.644027, points=82.488168. Prior BEST `run-aad4ae1ad447` had K=23.892877. The 86.85% K increase outweighs the larger source axis; promote the exact `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` source. Rollback is parent commit `2b5afc9`, source blob `1d59a36e5166f19cbf870f6458da5179f17bf1ed`.


## Staged six-physical-core default — 2026-10-31

- Candidate source blob `ea7cdf2a960168dd13a729baedca7ad3b990dde6` from `sd-ta/main` latest source commit `ff2073649af1fe8f2d0b33883c765e16458cdbe2`; latest documentation head `f1e501c88073b993c3253bdd74b195d7875e7677`. Default parser workers are capped at six physical P-cores; `SD_THREADS` remains available for validation.
- Exact-source CI `41200171027` passed official hashes, seed-2/3 differential, adversarial ordering, ASan/UBSan, TSan and restricted offline Docker. Paired 31-run full medians: 0.041953 s before vs 0.041843 s after; median cgroup peak 6.93 vs 6.14 MB, with a prior 14.06 MB maximum outlier. Developer proxy estimates +2.6% K; this is not an official six-P-core measurement. Candidate board result is pending. Rollback to prior exact scored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is commit `7f6c7fd`.


## Six-core default official trial — rejected, 2026-10-31

- Run `run-183210913374` scored `ca8f1811fcefc6fdb6cc5678754f7387791f5f31`; all five gates passed. Candidate LATEST: T=0.028955 s, M=16,785,408 B, S=443, D=1, K=41.105096, points=80.694784. BEST remains `run-383d474cf6f7`, K=44.644027 on the prior source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`; the new default lost 7.93% K despite lower M. Restore that scored source; six-core-cap candidate `ea7cdf2a960168dd13a729baedca7ad3b990dde6` remains recoverable in `ca8f181`.

## Official latest — 2026-10-31 12:21:24 UTC

- **BEST:** `run-383d474cf6f7`, K=44.644027. **LATEST:** `run-183210913374`, T=0.028955 s, M=16,785,408 B, S=443, D=1, K=41.105096; all gates passed. Source is now restored to the BEST candidate pending a rescore.


## Official latest — 2026-10-31 12:26:53 UTC

- **BEST and LATEST:** `run-2e35ec2bc727` on `f3b24e34ddb937f3bca3317cfd5d79bf021509fa`; all five gates passed. T=0.022370 s, M=20,779,008 B, S=442, D=1, K=44.826321, points=82.576655. This is 0.41% above prior BEST `run-383d474cf6f7` (K=44.644027); source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` remains promoted.


## Official latest — 2026-10-31 12:33:30 UTC

- BEST remains `run-2e35ec2bc727`, K=44.826321. LATEST `run-78a511c4249d` on `f477933130ce23aa311f60d3486480ab5de6fff8` passed all five gates: T=0.022724 s, M=20,824,064 B, S=442, D=1, K=44.456530. The 0.83% gap is run variation; source `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is unchanged.


## Official latest — 2026-10-31 12:40:38 UTC

- **BEST:** `run-2e35ec2bc727`, K=44.826321. **LATEST:** `run-9aa98021de01` on `0923ede528139a79896a6bfe1bb67934f74c5951`, all five gates passed: T=0.022471 s, M=20,774,912 B, S=442, D=1, K=44.727231, points=82.528601. Same promoted source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`; 0.22% below BEST, consistent with run variation.

## Official same-source rerun — 2026-10-31 13:17 UTC

- Run `run-405c0127303d` on `b0e30144ba58e2c3b3c86c8b1fd26dffa1e655b5` passed all five gates: T=0.022681 s, M=20,664,320 B, S=442, D=1, K=44.567239. BEST remains `run-2e35ec2bc727` (K=44.826321). Source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is unchanged; this is a repeat measurement, not a new candidate.


## Official latest — 2026-10-31 13:23:53 UTC

- **BEST:** `run-2e35ec2bc727`, K=44.826321. **LATEST:** `run-87abaa55cd94` on `f1bcd2033e061028929c445c964768331d1a6f5e`, all five gates passed: T=0.023130 s, M=20,910,080 B, S=442, D=1, K=44.028318, points=82.186605. Source remains `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`; no A source change was in this run.


## Official latest — 2026-10-31 14:17 UTC

- BEST remains `run-2e35ec2bc727`, K=44.826321. LATEST `run-b5f6e3dce3cd` on `af33cf8053e100e92405aabcfa50d0278203daa1` passed all five gates: T=0.022445 s, M=21,393,408 B, S=442, D=1, K=44.491316, points=82.413763. A source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` was unchanged.


## Official latest — 2026-10-31 14:22 UTC

- BEST remains `run-2e35ec2bc727`, K=44.826321. LATEST `run-9c28b89f6393` on `e5e94a469faec38eaaf180210e468ac3060b3023` passed all five gates: T=0.023166 s, M=20,541,440 B, S=442, D=1, K=44.150879, points=82.246968. Source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` was unchanged.

## Official latest — 2026-10-31 15:12 UTC

- LATEST `run-a4f58a34118c` on `1657706f033d676bb97f0df87e3386978b694387` passed all five gates: T=0.023361 s, M=20,926,464 B, S=442, D=1, K=43.803233, points=82.075308. BEST remains `run-2e35ec2bc727`, K=44.826321. Track A source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` was unchanged.

## Official latest — 2026-10-31 15:21 UTC

- LATEST `run-f9bae0db8920` on `480a8e3def26af26e10298d6b043bf2195c82ec3` passed check/build/correctness/timeout/sandbox: T=0.022646 s, M=20,787,200 B, S=442, D=1, K=44.548810, points=82.441805. BEST remains `run-2e35ec2bc727`, K=44.826321. The scored A source blob was `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`.

## Streaming hour-epoch architecture — later withdrawn after ThreadSanitizer failure, 2026-10-31

- Candidate from open `sd-ta` PR #1, commit `fe290bbd1f0959bbf05654075177a8f9d6d5b1dc`; exact source/Docker blobs `2d60fab7bc533d01c31167ca0cd5d66216013ec9` / `c934107df70396661fe1d2c29b9f579fcf9edcb2`. Both blobs match successful exact-source CI `41182862751` (commit `e170a65`): seed-1 hashes, seed-2/3 references, reordered inputs, endpoint/latency/group edge tests, ASan/UBSan and allowlisted offline Docker passed.
- CI paired 31-run full medians: champion 0.103322 s vs candidate 0.047562 s on its 4-vCPU runner; cgroup peaks 41,041,920 vs 6,348,800 B; reported S 321 vs 441. Strong candidate evidence, but not scoring-box evidence.
- Official run `run-b447dc4b353e` on submission commit `8298e2cbe0d21ffd4688bb23b625f988fdd4128d` passed all five gates: T=0.020573 s, M=21,041,152 B, S=441, D=1, K=46.641863, points=83.438795. This is the new BEST and LATEST, 4.05% above `run-2e35ec2bc727` (K=44.826321). PR #1 was merged into `sd-ta/main` at `5171eeeb24451b28cf5878a199d2abe389a9e848`; parent `480a8e3def26af26e10298d6b043bf2195c82ec3` retains the prior source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` for rollback.


## Post-merge sanitizer failure and rollback — 2026-10-31

- GitHub Actions runs `41218843179` (merge commit `5171eeeb24451b28cf5878a199d2abe389a9e848`) and `41219011089` (A main `6370e4ce4738ab32ade991c17aa5a7083df8e54a`) both failed the `ThreadSanitizer dictionary and output smoke` step. Earlier exactness, full hashes, reorder, and ASan/UBSan steps passed. TSan reported a race between atomic bucket-tag write in `Names::add` (line 183) and non-atomic SIMD vector tag read in `lookup` (line 144); treat as a correctness/safety defect and do not promote this candidate until fixed and requalified.
- Board-only **raw BEST** `run-b447dc4b353e` on `8298e2cbe0d21ffd4688bb23b625f988fdd4128d`: all board gates passed, T=0.020573 s, M=21,041,152 B, S=441, D=1, K=46.641863, points=83.438795. **LATEST** `run-8b0b8f3bb20b` on `d4b9c4d51f4d0c3fc2d58a1fc9bf6c66ef642ed9`: all board gates passed, T=0.021097 s, M=21,209,088 B, S=441, D=1, K=45.985812, points=83.131193. These scores do not clear the independent TSan failure.
- Restore the previously correctness-qualified Track A source from release parent `480a8e3def26af26e10298d6b043bf2195c82ec3` (source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`). Its board BEST remains `run-2e35ec2bc727`, K=44.826321. The new release commit records this source rollback; wait for its actual latest board run before updating LATEST.


## Official latest after Track A rollback — 2026-10-31 16:27 UTC

- LATEST `run-dd3f5e9ed0ae` on official commit `70d512481b36d111e017909f4b76e257f69db9ea` passed all five board gates: T=0.022796 s, M=21,409,792 B, S=442, D=1, K=44.140702, points=82.241962. The verified prior source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is restored. Promotion-qualified BEST remains `run-2e35ec2bc727`, K=44.826321; the higher raw candidate score is withheld due to TSan failures above.

## Official latest after A rollback — 2026-10-31 16:33 UTC

- LATEST `run-8ea30eda904d` on official commit `0ef3758e08e015c6f1ba97b9d36966ec151efc40` passed all five board gates: T=0.022901 s, M=20,877,312 B, S=442, D=1, K=44.261784, points=82.301446. Restored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` remains correctness-qualified; valid-source BEST `run-2e35ec2bc727`, K=44.826321. The raw score-only BEST `run-b447dc4b353e` is excluded from promotion because TSan reported a race.


## Full-team board results — 2026-10-31 16:39–16:45 UTC

All five gates passed on both commits. Track A source was the restored correctness-qualified blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`; no A source change occurred between these runs.

- **BEST (correctness-qualified):** `run-2e35ec2bc727`, K=44.826321. The higher raw score `run-b447dc4b353e` is excluded after TSan found a race in withdrawn PR #1.
- **LATEST:** `run-3d872bd24c7b` on official commit `242c9bf8b5169359fbe30b30245cf799f1662304`: T=0.022768 s, M=20,471,808 B, S=442, D=1, K=44.565355, points=82.449869.
- Previous receipts: `run-d22b40c8ce45` on `92c095f030bd9519de41ab7201a944cc9d94cbd6`: T=0.022801 s, M=20,779,008 B, S=442, K=44.400631; `run-8ea30eda904d` on `0ef3758e08e015c6f1ba97b9d36966ec151efc40`: K=44.261784.
- The 242 score improves the latest measurement by 0.37%; it remains 0.58% below the correctness-qualified BEST. No A promotion is claimed.


## Full-team board run — 2026-10-31 16:49 UTC

All five gates passed on official commit `6a01ff11b17d179835197e73cbab6518a6651b79`.

- **LATEST:** `run-66138309f3ff`: T=0.022393 s, M=21,299,200 B, S=442, D=1, K=44.582278, points=82.458113.
- The restored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is unchanged. Correctness-qualified **BEST** remains `run-2e35ec2bc727`, K=44.826321. No A promotion.


## Full-team board run — 2026-10-31 16:54 UTC

All five gates passed on commit `77a70106fecd5098a0a152a47f8e7383a3c1e9c5`: `run-97a255fa21e7`, T=0.022728 s, M=20,451,328 B, S=442, D=1, K=44.613484, points=82.473307. The restored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` is unchanged. Correctness-qualified BEST remains `run-2e35ec2bc727`, K=44.826321.


## Latest after B rollback — 2026-10-31 17:00 UTC

Commit `74a4fb7456ce5fb8b10ef5b0eeef2d58289fdc59` passed all five gates. **LATEST:** `run-0a2099ff0770`, T=0.023064 s, M=20,779,008 B, S=442, D=1, K=44.146754, points=82.244939. Source remains the restored blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`; correctness-qualified BEST `run-2e35ec2bc727` remains K=44.826321.


## Full-team board run — 2026-10-31 17:05 UTC

All five gates passed on official commit `23be16823a7232064b3090b805ff80b6c086cfa9`. **LATEST:** `run-89a07b1ad96a`, T=0.022670 s, M=20,348,928 B, S=442, D=1, K=44.715386, points=82.522849. The restored source remains unchanged; correctness-qualified BEST `run-2e35ec2bc727` remains K=44.826321.


## Full-team board results and new race-free trial — 2026-10-31 17:10 UTC

All five official gates passed on commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818` using the restored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`. **LATEST:** `run-206e1644af83`, T=0.022396 s, M=20,873,216 B, S=442, D=1, K=44.759781, points=82.544398. Correctness-qualified BEST remains `run-2e35ec2bc727`, K=44.826321; the higher raw BEST `run-b447dc4b353e` is excluded because TSan found a race.

## Candidate from sd-ta main staged for official scoring

- Staged source blob `f364d2123e1fde3869ab6a79fc6e0c85ba5aa085` from developer HEAD `961cf366d3b3bbd0b806d340bd75dd9246803fd1`. CI [41222270123](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41222270123) succeeded. The source is the acquire-load threshold-16 dictionary implementation with six-byte records and six-worker default; CI [41217509351](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41217509351) passed official hashes, seed 2/3, disorder, ASan/UBSan, TSan and restricted Docker.
- Paired 31-run CI full-input medians were 0.037612 s for the previous six-worker champion and 0.037453 s for this source (0.42% faster); max cgroup peaks were 8,347,648 B and 7,045,120 B. This is CI evidence, not an official board score.
- Official trial is pending. The previous official A source remains in parent commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818` for rollback. Do not promote until the official gates pass and K beats the correctness-qualified BEST.


## Race-free threshold-16 candidate — official trial rejected — 2026-10-31 17:20 UTC

Candidate source blob `f364d2123e1fde3869ab6a79fc6e0c85ba5aa085` from `sd-ta/main` passed all five official gates on commit `c4cb49fedd910dd65dc0719c113b06fa2e9c2476`. Run `run-c4f4c1b69380`: T=0.027990 s, M=16,519,168 B, S=447, D=1, K=41.885064, points=81.102959.

- Versus the immediately preceding race-free source result `run-206e1644af83` (T=0.022396 s, M=20,873,216 B, S=442, K=44.759781), memory fell 20.8%, but T rose 25.0%, S increased by 5, and K fell 6.4%. It also failed to beat correctness-qualified BEST `run-2e35ec2bc727`, K=44.826321. CI's 0.42% local timing gain did not carry over to the scoring box.
- Reject for promotion and restore source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` plus its README from parent commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818`. The candidate remains in official history for reference; no developer repository was modified.


## Official baseline on rollback HEAD — 2026-10-31 17:30 UTC

Commit `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122` passed all five gates with restored source blob `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c`. **LATEST:** `run-ef514c9b115e`, T=0.022955 s, M=20,819,968 B, S=442, D=1, K=44.234018, points=82.287820. Correctness-qualified BEST remains `run-2e35ec2bc727`, K=44.826321; the higher raw BEST `run-b447dc4b353e` remains excluded for its TSan race.

## New 12-worker atomic-pair candidate staged

- Developer main HEAD `79c8f22d59461e4cf3a39fccff8cab2070759cd9`, source blob `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a`, uses atomic pair publication/acquire reads, exact endpoint-byte checks and up to twelve logical workers. CI [41227986546](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41227986546) passed official hashes, seed 2/3, disorder, ASan/UBSan, TSan, restricted Docker and paired comparisons.
- CI's 31-run four-vCPU medians were 0.051800 s for `ff20736` and 0.049822 s for this candidate (3.82% faster); peak cgroup samples were 6,381,568 and 6,754,304 B. This is local evidence only; twelve-worker scaling and official K are unmeasured.
- This differs from the failed six-worker threshold-16 trial. Preserve rollback source `a4a487a0e1ddebe51f27d1af7eb90c98faf12e0c` in parent `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122`. Promote only if official gates pass and K beats correctness-qualified BEST.


## Official promotion — run-18b717b066d6 (2026-10-31 18:17 UTC)

- Promoted Track A source blob `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a` from developer `sd-ta` main HEAD `79c8f22d59461e4cf3a39fccff8cab2070759cd9`. All five board gates passed.
- Official **BEST/LATEST**: `run-18b717b066d6`, T=0.021878 s, M=20,811,776 B, S=460, D=1, K=45.042769, points=82.681254.
- Prior correctness-qualified BEST was `run-2e35ec2bc727`, K=44.826321. K improved by 0.216448 (+0.48%). A higher raw board record remains excluded because its source had a confirmed TSan race.
- Previous race-free source remains available at parent checkpoint `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122`.


## Official results — run-28140e0a9651 (2026-10-31 18:25 UTC)

- All five gates passed on commit `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`.
- **BEST/LATEST:** `run-28140e0a9651`; T=0.021664 s, M=20,992,000 B, S=460, D=1, K=45.186701, points=82.750532. This is the same promoted source as `run-18b717b066d6`; the new run improves its prior K 45.042769.


## Official results — run-b7ad796c1836 (2026-10-31 18:31 UTC)

All five gates passed on unchanged promoted source. **LATEST and correctness-qualified BEST:** `run-b7ad796c1836`, T=0.021286 s, M=21,233,664 B, S=460, D=1, K=45.481911, points=82.891935. It improves the previous correctness-qualified BEST `run-28140e0a9651` (K=45.186701). Raw board BEST `run-b447dc4b353e` remains excluded because its source had a confirmed TSan race.


## Official latest — run-2831a9dce075 (2026-10-31 18:37 UTC)

All five gates passed on the unchanged promoted source. **LATEST:** T=0.021403 s, M=21,184,512 B, S=460, D=1, K=45.378455, points=82.842485. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911); raw BEST `run-b447dc4b353e` remains excluded for the confirmed TSan race.


## Official latest — run-45c895744595 (2026-10-31 18:44 UTC)

All five gates passed. **LATEST:** T=0.021607 s, M=20,467,712 B, S=460, D=1, K=45.475724, points=82.888981. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911); raw board BEST `run-b447dc4b353e` is excluded for the TSan race.


## Official latest — run-b9b31b4c4e0e (2026-10-31 18:50 UTC)

All five gates passed. **LATEST:** T=0.021573 s, M=21,127,168 B, S=460, D=1, K=45.223814, points=82.768360. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911).


## Official latest — run-c25758e8dcaf (2026-10-31 18:56 UTC)

All five gates passed. **LATEST:** T=0.021560 s, M=20,811,776 B, S=460, D=1, K=45.373733, points=82.840226. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911).


## Official latest — run-be9e7d11d1b2 (2026-10-31 19:02 UTC)

All five gates passed. **LATEST:** T=0.021633 s, M=21,106,688 B, S=460, D=1, K=45.169817, points=82.742416. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911).


## Official latest — run-e916246a1d9c (2026-10-31 19:08 UTC)

All five gates passed. **LATEST:** T=0.022484 s, M=21,565,440 B, S=460, D=1, K=44.116624, points=82.230113. **Correctness-qualified BEST** remains `run-b7ad796c1836` (K=45.481911).


## Official latest — run-0577d3068f59 (2026-10-31 19:15 UTC)

All five gates passed. T=0.021133 s, M=20,795,392 B, S=460, D=1, K=45.837056, points=83.060836. The source blob is unchanged from the correctness-qualified A champion; record this as **LATEST** and measured **BEST** (prior best `run-b7ad796c1836`, K=45.481911). The earlier higher raw K from `run-b447dc4b353e` remains excluded due to TSan race evidence.


## Official latest — run-e84ec0c9422a (2026-10-31 19:24 UTC)

All five gates passed. **LATEST:** T=0.022452 s, M=21,463,040 B, S=460, D=1, K=44.190097, points=82.266248. **BEST** remains `run-0577d3068f59` (K=45.837056); the A source blob is unchanged.


## Official latest — run-aa16aefdad04 (2026-10-31 19:29 UTC)

All five gates passed. **LATEST:** T=0.021266 s, M=20,938,752 B, S=460, D=1, K=45.630755, points=82.962883. **BEST** remains `run-0577d3068f59` (K=45.837056).

## Frontier PR #3 trial

Submitted source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` from exact open PR head `5b931802c42bd4c028f18513cbf56bc6b4c1424a`. Exact source and build context match successful CI `41233423569` at `db4c98a`; 4-vCPU paired median was 0.780x the pinned champion, while `memory.peak` rose 5.73→6.02 MB. This is local evidence, not official K. Rollback source is `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a`; **BEST remains `run-0577d3068f59`** pending official scoring. Merge PR #3 only if promoted.


## Frontier PR #3 official result — run-92205f3fba85 (2026-10-31 19:37 UTC)

All five gates passed, but the candidate regressed: T=0.021915 s, M=24,838,144 B, S=584, D=1, K=41.912918, points=81.117395. This is below BEST `run-0577d3068f59` (K=45.837056), with higher memory and source size. **Reject PR #3 for promotion** and restore source `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a`; PR remains open and unmerged.


## Official latest — run-b8ebedebd8ce (2026-10-31 19:42 UTC)

All five gates passed on restored A champion. **LATEST:** T=0.021866 s, M=20,934,656 B, S=460, D=1, K=45.002111, points=82.661644. **BEST** remains `run-0577d3068f59` (K=45.837056).

## Official board run — 2026-10-31 19:46 UTC

Run `run-b8ebedebd8ce` scored commit `2602c63339f532be813056b0c05bb573835f6766`; all five gates passed, failure null. **LATEST:** T=0.021866 s, M=20,934,656 bytes, S=460, D=1, K=45.002111. **BEST** remains `run-0577d3068f59`, K=45.837056 (same source blob `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a`).

### Frontier PR #2 official trial

Staged `sd-ta` PR #2 exact head `50b33bb7d0085acf296e5f34a55e30b4958fb07d` (source blob `24926c0187974683c9e96ebac46d48073d5907d5`) for official scoring. Exact-head CI run `41232109362` passed, including size regressions and ThreadSanitizer at 6 and 12 workers. Developer-reported 4-vCPU local CPU time 180→115 ms and wall time 52–60→36–39 ms; these are not official-box measurements. Known-good rollback remains source blob `7c5a2253b50e5f9c0fe284de3fa384c01ef1cd4a`.

## Official board result — commit 3384246, dispatch 2026-10-31 19:52 UTC

Run `run-f5acb6219cc9`; all five gates passed. T=0.018912 s, M=21,667,840 bytes, S=574, D=1, K=46.487453, points=83.366788. **Verified BEST and LATEST:** this PR #2 source exceeds the prior correctness-qualified BEST `run-0577d3068f59` K=45.837056. The raw board's numeric BEST `run-b447dc4b353e` K=46.641863 is excluded as a candidate because its source has the reported TSan race. Developer CI exact-head run `41232109362` passed the additional size cases and TSan at 6/12 workers.

PR #2 was promoted and merged to `sd-ta/main` as `82493a17ff0d784abbaa35f23590e10545724fe9`.

## Official board result — commit 13b8fec, dispatch 2026-10-31 19:57 UTC

Run `run-b69ecc476b37`; all five gates passed. T=0.019740 s, M=21,311,488 bytes, S=574, D=1, K=45.653206, points=82.973564. **BEST:** `run-f5acb6219cc9`, K=46.487453 (qualified A PR #2). **LATEST:** `run-b69ecc476b37`.

## Official board result — commit 555cd61, dispatch 2026-10-31 20:03 UTC

Run `run-1d2fdbfbdd62`; all five gates passed. T=0.016499 s, M=21,671,936 bytes, S=574, D=1, K=49.769039, points=84.847963. **BEST = LATEST:** this repeat scores the same qualified A PR #2 source at K=49.769039; prior `run-f5acb6219cc9` was K=46.487453. PR #3's updated head `ac9ff0330732506848426209b86d9f5739d662f6` has the same source blob as its earlier official trial (`c91b9689...`), already measured at K=41.912918, so it is not resubmitted. The new PR head also adds a tracked `.pyc`; do not promote it.


## Official board result — trial commit 9743d05 (2026-10-31 20:09:57 UTC)

Run `run-69ce79d9c733`; all five gates passed. T=0.019080 s, M=21,590,016 B, S=574, D=1, K=46.315657, points=83.286392. **BEST** remains `run-1d2fdbfbdd62` at K=49.769039; this repeat of the qualified PR #2 source is **LATEST**, not a new best.


## Official board result — commit 3c9845a (2026-10-31 20:15:02 UTC)

Run `run-dc158b747f2c`; all five gates passed. T=0.019502 s, M=20,877,312 B, S=574, D=1, K=46.120406, points=83.194656. **LATEST** is this restored champion-source run; **BEST** remains `run-1d2fdbfbdd62` at K=49.769039.


## Official board result — commit fa0f0b4 (2026-10-31 20:20:02 UTC)

Run `run-6142b9dc0cf7`; all five gates passed. T=0.019840 s, M=21,368,832 B, S=574, D=1, K=45.513540, points=82.907031. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` at K=49.769039.


## Official board result — commit c2397c9 (2026-10-31 20:26:59 UTC)

Run `run-d46f43822d2d`; all five gates passed. T=0.019889 s, M=21,893,120 B, S=574, D=1, K=45.237605, points=82.774980. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).

## Developer-main reserve experiment (not promoted)

Head `7cc853baacbbb5b81c221120558e891f824482d4` removes the unconditional 131,072-element reserve from the per-hour latency vector (source blob `6a3de1a8645ae929cd4181e979d4e97275175ea9`). Exact-head workflow `41241963933` passed differential tests, official hashes, seed-2/3 holdout samples, ASan/UBSan, TSan, offline Docker, runtime comparison and cgroup-memory measurement. Its log reported 31-run local medians 0.032782 s vs `six-worker-base` 0.039465 s (ratio 0.8307); RSS was 238,508 KiB vs 239,068 KiB, while five-run cgroup `memory.peak` max was 10.84 vs 9.52 MB, so memory evidence is mixed. The newer A main head `f4cfe46184d9ab26be62cdfcbde90c069fdc1305` restored the qualified source after mixed local evidence. It was nevertheless dispatched as commit `74145b5`; the official run below failed to beat BEST, so the candidate remains rejected and unmerged.


## Official board result — reserve experiment commit 74145b5 (2026-10-31 21:10:54 UTC)

Run `run-1b5d6f0f85e2`; all five gates passed. T=0.017067 s, M=22,142,976 B, S=573, D=1, K=48.736620, points=84.392770. This exact A source (one-line reserve removal) is below BEST `run-1d2fdbfbdd62` (K=49.769039); **reject** and keep qualified source blob `24926c0187974683c9e96ebac46d48073d5907d5`, restored on official HEAD `89f8c72`.

## Developer-main batch-eviction experiment (not submitted)

Current A main `e96477afdefbb530e105d19329ebdfa53d6fbe89` batches output `posix_fadvise` calls every four hours. Exact-head CI `41242381794` passed correctness, sanitizer, offline Docker and measurement steps. The workflow’s 31-run full-input median was 0.034935 s vs its six-worker baseline 0.034117 s (ratio 1.024); RSS was 247,588 vs 238,020 KiB, and five-run cgroup peak max was 17,633,280 vs 7,823,360 bytes. Reject pending stronger evidence; no official score claimed.


## Official board result — champion-only commit ac7ea0e (2026-10-31 21:15:54 UTC)

Run `run-ae9dd9cbff75`; all five gates passed. T=0.017357 s, M=21,176,320 B, S=574, D=1, K=48.748379, points=84.398009. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).

## Developer-main page-cache incremental trial (not submitted)

Exact head `dffb9732e29da8f759cc54f37c38c5308fb96a40` advises newly completed page-aligned output ranges each hour. CI `41242567022` passed official hashes, differential tests, ASan/UBSan, TSan, offline Docker and full-input measurements against the exact qualified base. Local 31-run full-input median was 0.040140 s vs 0.040003 s (ratio 1.0034); RSS 238,052 vs 238,244 KiB; cgroup peak max 6,791,168 vs 7,512,064 B over five runs. These measurements are essentially neutral and code adds three net lines, so no official trial is planned. Keep source blob `24926c0187974683c9e96ebac46d48073d5907d5`.


## Official board result — commit 260134e (2026-10-31 21:23:17 UTC)

Run `run-be642e5327e0`; all five gates passed. T=0.018885 s, M=21,188,608 B, S=574, D=1, K=46.729231, points=83.479432. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).


## Official board result — commit 954e3c7 (2026-10-31 22:12:50 UTC)

Run `run-cc8e89b28794`; all five gates passed. T=0.022193 s, M=20,975,616 B, S=574, D=1, K=43.193327, points=81.770833. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).


## Official board result — commit 62eaaeb (2026-10-31 23:10:08 UTC)

Run `run-aaa6c2267f2d`; all five gates passed. T=0.019977 s, M=21,442,560 B, S=574, D=1, K=45.325974, points=82.817357. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).

## Frontier PR #3 candidate — rejected by official score

Imported only track-a/main.cpp from PR #3 head `ac9ff0330732506848426209b86d9f5739d662f6`; source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` exactly matches the source tested by CI `41233423569` (run head `db4c98a`). Developer CI reports all gates passed, 4-vCPU median 0.780x the pinned champion, with memory.peak 6.02 vs 5.73 MB. That is promising runtime evidence with a modest memory increase; official run on commit 97ebf28 passed all gates but scored K=46.473909, below BEST K=49.769039; candidate rejected, prior source retained for rollback. The PR also contains a generated pyc test artifact; it is excluded from the official import. Previous A champion remains in parent `62eaaeb` for rollback.


## Official board result — commit 97ebf28 (2026-10-31 23:15:08 UTC)

Run `run-63dc03eb17bc`; all five gates passed. T=0.019015 s, M=21,131,264 B, S=584, D=1, K=46.473909, points=83.360460. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039). The PR #3 source candidate was not promoted.


## Official board result — commit c096950 (2026-10-31 23:55:08 UTC)

Run `run-343ccd3f8d7a`; all five gates passed. T=0.019102 s, M=21,614,592 B, S=584, D=1, K=46.158707, points=83.212682. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).


## Official board result — commit 7dc6a03 (2026-10-31 23:58:28 UTC)

Run `run-58030833c069`; all five gates passed. T=0.019781 s, M=21,577,728 B, S=584, D=1, K=45.375059, points=82.840860. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039). PR #3 source remains rejected; restore the known-good A source blob `24926c0187974683c9e96ebac46d48073d5907d5`.


## Official board result — commit f8cfd3d (2026-11-01 00:10:50 UTC)

Run `run-db5b7041e475`; all five gates passed. T=0.022740 s, M=21,594,112 B, S=574, D=1, K=42.423384, points=81.380266. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).


## Official board result — commit eeef411 (2026-11-01 00:17:52 UTC)

Run `run-f898142a9c05`; all five gates passed. T=0.018859 s, M=22,114,304 B, S=574, D=1, K=46.363224, points=83.308681. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).

## Official board result — commit d1cb0e5 (2026-11-01 00:22:52 UTC)

Run `run-d64edd32beff`; all five gates passed. T=0.020719 s, M=20,934,656 B, S=574, D=1, K=44.720850, points=82.525502. **LATEST before the two-stream trial**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039). This exact A source blob `24926c0187974683c9e96ebac46d48073d5907d5` is also the source from merged A PR #2; it is retained as the known-good four-stream rollback.

## Mainline two-stream candidate — rejected by official score

Candidate from A main `cbfe267c5fc50fb52125484259dcb6d43913b8fa`, source blob `9e98a8a28d5d34aeee5cb2badd6817b981d33c16`, changes per-block parser interleaving from four streams to two; all other source lines match the prior official A source. CI `41254978151` passed full/tiny/sample hashes, seed-2/3 differential, disorder, ASan/UBSan, TSan, offline Docker, and size checks. Paired 31-run full-input CI median was 0.039806 s for qualified base and 0.039400 s for candidate (1.02% faster); five-run cgroup memory.peak maxima were 6,610,944 B and 7,954,432 B respectively, so the runtime gain has a memory tradeoff. A local host compile passed (1,487,080-byte executable); the integrated Docker build could not register the pinned gcc layer because this Docker daemon ran out of storage. Official run `run-6698591dc331` on `660ecd0` passed all gates: T=0.018735 s, M=21,590,016 B, S=574, D=1, K=46.740157, points=83.484508. It did not beat BEST K=49.769039; reject this variant and restore the four-stream source blob `24926c0187974683c9e96ebac46d48073d5907d5` in the next checkpoint. Parent `d1cb0e5` preserves the prior source.

## Official board result — commit cf46ad7 (2026-11-01 00:32:52 UTC)

Run `run-74c0b9c2985d`; all five gates passed. T=0.018832 s, M=21,082,112 B, S=574, D=1, K=46.842122, points=83.531828. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039). This run used the restored four-stream A champion source blob `24926c0187974683c9e96ebac46d48073d5907d5`.


## Official board result — commit b665afd (2026-11-01 00:37:52 UTC)

Run `run-96f92ca92b57`; all five gates passed. T=0.019819 s, M=21,573,632 B, S=574, D=1, K=45.450858, points=82.877104. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).


## Official board result — commit 925095f (2026-11-01 00:42:54 UTC)

Run `run-1ddb335c734c`; all five gates passed. T=0.019901 s, M=21,303,296 B, S=574, D=1, K=45.471659, points=82.887040. **LATEST**; **BEST** remains `run-1d2fdbfbdd62` (K=49.769039).

## Frontier PR #3 — official BEST; promoted and merged

Candidate source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` is an in-place output/writeback and worker-start change layered on the already merged PR #2 source. Exact source was exercised by CI `41233423569` (workflow head `db4c98a`): full/sample/tiny references, holdout samples, reordering, ASan/UBSan, TSan, Docker allowlist/offline sandbox, and scored-style cgroup checks all passed. Developer 4-vCPU end-to-end median was 0.780x the pinned champion, with peak memory 6.02 vs 5.73 MB (+5.1%); this is a developer measurement, not board T/M/S/D/K. Dockerfile matches the official track-A build. The PR includes an unneeded `__pycache__` artifact; only `main.cpp` is imported. Rollback remains the prior PR #2 source in parent `925095f`.


## Official board result — commit 16126e3 (2026-11-01 00:47:54 UTC)

Run `run-b48d347e17a7`; all five gates passed. PR #3 source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.016783 s, M=21,340,160 B, S=584, D=1, K=49.370569, points=84.673407. **LATEST**, not promoted: **BEST** remains `run-1d2fdbfbdd62` (K=49.769039). This is 0.80% below BEST, despite beating the preceding A run substantially; a confirmatory official run was queued because the CI speed claim was meaningful and the first result was close.


## Official result and promotion — commit 12673d7 (2026-11-01 00:52:54 UTC)

Run `run-118836ebd34c`; all five gates passed on PR #3 source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.016388 s, M=21,344,256 B, S=584, D=1, K=49.960098, points=84.931164. **BEST = LATEST**, +0.38% over `run-1d2fdbfbdd62` (K=49.769039). PR #3 is promoted and merged to `sd-ta/main` at `306c538a4c2d9bdbcf830652f947df69fa5ca213`; the previous A source remains in official parent `925095f`.


## Official board result — commit 32bcf03 (2026-11-01 00:57:54 UTC)

Run `run-505031036f92`; all five gates passed. Same promoted PR #3 source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.019739 s, M=21,422,080 B, S=584, D=1, K=45.489123, points=82.895378. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Compared with that same-source run, T varied 20.5% while M changed 0.36%; keep the candidate, record the spread, and revalidate the exact head.

## Official board result — commit 033819b (2026-11-01 01:02:54 UTC)

Run `run-4cb91c778afa`; all five gates passed. T=0.019293 s, M=21,508,096 B, S=584, D=1, K=45.975048, points=83.126110. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.


## Official board result — commit 832a496 (2026-11-01 01:07:54 UTC)

Run `run-eafdfb89b7af`; all five gates passed. T=0.022712 s, M=22,994,944 B, S=584, D=1, K=41.810784, points=81.064415. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source blob. The across-track slowdown warrants a clean champion rerun before further tuning.


## Official board result — commit bc48c37 (2026-11-01 01:12:54 UTC)

Run `run-ed0ed9df98dc`; all five gates passed. T=0.020108 s, M=21,360,640 B, S=584, D=1, K=45.095705, points=82.706759. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source blob.


## Official board result — commit 62c5bf4 (2026-11-01 01:17:54 UTC)

Run `run-34b2d7bd448d`; all five gates passed. T=0.021896 s, M=21,217,280 B, S=584, D=1, K=43.273511, points=81.811107. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same source.


## Official board result — commit d411050 (2026-11-01 01:22:54 UTC)

Run `run-e022f8648f11`; all five gates passed. T=0.019144 s, M=21,504,000 B, S=584, D=1, K=46.155374, points=83.211114. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source.


## Official board result — commit 132ef00 (2026-11-01 04:06:36 UTC)

Run `run-e3a1c1f0b5be`; all five gates passed. T=0.017615 s, M=21,221,376 B, S=584, D=1, K=48.244347, points=84.172322. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same source.

## Official board result — commit 4a4461e (2026-11-01 04:11:36 UTC)

Run `run-88c7e38bf865`; all five gates passed. T=0.021463 s, M=22,413,312 B, S=584, D=1, K=43.231076, points=81.789802. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source.

## Official board result — commit a13b5ef (2026-11-01 04:16:46 UTC)

Run `run-3c456ffa2082`; all five gates passed. T=0.019652 s, M=21,663,744 B, S=584, D=1, K=45.487533, points=82.894619. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source.
Sequential same-source board comparison: `run-88c7e38bf865` to `run-3c456ffa2082`, K 43.231076→45.487533 (+5.22%), T 0.021463→0.019652 s (-8.44%), M 22,413,312→21,663,744 B (-3.34%). Keep historical BEST; this repeat quantifies scoring variation.

## Official board result — commit 0e56118 (2026-11-01 04:23:34 UTC)

Run `run-706e50daa774`; all five gates passed. T=0.016590 s, M=21,245,952 B, S=584, D=1, K=49.700875, points=84.818202. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source.

## Official board result — commit f281e05 (2026-11-01 04:30:02 UTC)

Run `run-cdbb44fa1823`; all five gates passed. T=0.016973 s, M=20,955,136 B, S=584, D=1, K=49.272553, points=84.630253. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same A source.

## Official board result — commit 1633378 (2026-11-01 04:36:05 UTC)

Run `run-1611d13f0c3d`; all five gates passed on the unchanged A PR #3 source. T=0.019959 s, M=20,914,176 B, S=584, D=1, K=45.455342, points=82.879246. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098) on the same source. This same-source repeat is below the previous LATEST `run-cdbb44fa1823` (K=49.272553); retain BEST and do not infer a source regression from one board run.

## Official board result — commit 116914f (2026-11-01 04:41:53 UTC)

Run `run-6f9ba21a52e5`; all five gates passed on the unchanged A PR #3 source. T=0.016999 s, M=21,229,568 B, S=584, D=1, K=49.106903, points=84.557127. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098), same source.

## Official board result — commit b5b3fec (2026-11-01 04:47:45 UTC)

Run `run-6524054f5aa0`; all five gates passed on unchanged A PR #3 source. T=0.018677 s, M=21,368,832 B, S=584, D=1, K=46.787814, points=83.506638. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board result — commit de9c67e (2026-11-01 04:53:02 UTC)

Run `run-efa9f52448ad`; all five gates passed on unchanged A PR #3 source. T=0.017414 s, M=21,221,376 B, S=584, D=1, K=48.521977, points=84.296924. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official `speed-demon` commit `eeec788784e06afa814bc442630cd2d3a1d42001`: run `run-619e73b6e7b2`, all five gates passed on unchanged Track A PR #3 source. T=0.019239 s, M=21,241,856 B, S=584, D=1, K=46.154359, points=83.210636. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Relative to the last same-source run `run-efa9f52448ad`, K and T vary downward by 4.88% and upward by 10.48%; no A source change.

- Repeat official run on source-identical commit `6917275dbd2ee12fd19df6fe3b87a60920c86ef8`: `run-6b660c85f1ed`, all five gates passed. T=0.019388 s, M=21,463,040 B, S=584, D=1, K=45.881511, points=83.081886. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). No A source change.

- Repeat official run on source-identical commit `17a6d96ba2cf813bac7eea2225b51fdd4d34960a`: `run-ea87ba793f05`, all five gates passed. T=0.016510 s, M=21,278,720 B, S=584, D=1, K=49.805790, points=84.863992. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). No A source change.

- Official run on `0d48c0b1302610385c4608b30b6842aa71e388cb`: `run-6567df7d7299`, all five gates passed on unchanged A PR #3 source. T=0.017840 s, M=21,585,920 B, S=584, D=1, K=47.776126, points=83.960546. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-434ebd60d4d5` on checkpoint `b70956dd71a72aec0c5bace4f41dcf3a9807f8ba`; all five gates passed on unchanged A PR #3 source. T=0.020811 s, M=21,110,784 B, S=584, D=1, K=44.431924, points=82.384756. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-c7e55a07625c` on `dde14ac917c8ad8642c734162b25804a4008cc90`; all five gates passed, unchanged A PR #3 source. T=0.020319 s, M=21,372,928 B, S=584, D=1, K=44.855789, points=82.590925. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-c0b8f1f7fd59` on `346a17e08d7356487484b804bbd9a0a456bfa4f5`; all five gates passed on unchanged A PR #3 source. T=0.017224 s, M=21,299,200 B, S=584, D=1, K=48.753163, points=84.400140. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-7ba51c8e9fff` on rollback checkpoint `d3af7efd6ac8fd8982cbaae3b759052ccd74547f`; all five gates passed on unchanged A PR #3 source. T=0.020153 s, M=21,061,632 B, S=584, D=1, K=45.172509, points=82.743711. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-3f1645458246` on `bf2de0f901f0e5bc2e1dc07331fd0de0622ff400`; all five gates passed on unchanged A PR #3 source. T=0.020317 s, M=20,889,600 B, S=584, D=1, K=45.063680, points=82.691333. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-9c879f4ce505` on `82d831033431c94a929d3c0eb99d62a0d061583a`; all five gates passed on unchanged A PR #3 source. T=0.021431 s, M=23,658,496 B, S=584, D=1, K=42.798034, points=81.571191. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-35745e9f9141` on `227bae88c5b80d003fdc3dda193ae499ffc8f66e`; all five gates passed on unchanged A PR #3 source. T=0.020412 s, M=21,532,672 B, S=584, D=1, K=44.686887, points=82.509005. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Official run `run-2a6ce9a594f5` on `dbbef62bc1668f45d4544f8fde7cb6c758996b68`; all five gates passed on unchanged A PR #3 source. T=0.020044 s, M=21,344,256 B, S=584, D=1, K=45.174574, points=82.744703. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).


## A PR #4 exact-catalog certificate — tested, not promoted

- Candidate is open draft PR #4 (`c6cc55f6`), exact source blob `e2713339cf44e515783d8671b1db074904070e3b`; rollback is selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`. The certificate activates only at the frozen exact 1,842-key catalog, compares full strings for colliding fingerprints, and falls back before saturation. No Docker or dependency changes.
- Two independent complete-program paired 31-run controls against current A main reported candidate/champion runtime ratios: CI `41290905376`: 0.9733x / 0.9582x / 0.9612x at 1/4/12 threads; CI `41290978319`: 0.9667x / 0.9501x / 0.9730x. Both exact-source CI workflows passed full/tiny/sample hashes, reference/random/reordered tests, ASan/UBSan, TSan, Docker sandbox and forced 42-way fingerprint-collision tests. These are runner ratios; candidate official M/S/K remain unmeasured.
- Official run `run-2b35fe185158` on commit `01966dd4c4464d08d4c2a5e44518a351cb102d07` used exact candidate source blob `e2713339cf44e515783d8671b1db074904070e3b`; all five board gates passed. T=0.019512 s, M=22,196,224 B, S=607, D=1, K=45.166806, points=82.740969. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098) on the previous A champion source.
- Versus the immediately preceding selected-source run `run-3ba931887dae` (T=0.020080 s, M=20,897,792 B, S=584, K=45.325284), this candidate is about 2.8% faster but uses 6.2% more memory and 23 more source lines; observed K is 0.35% lower. Not promoted; retain rollback source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.


## A PR #2 race-free SIMD candidate — official trial rejected

- Candidate is merged developer PR #2 head `50b33bb7d0085acf296e5f34a55e30b4958fb07d`, source blob `24926c0187974683c9e96ebac46d48073d5907d5`; imported exact `track-a/main.cpp`. It repairs the earlier shared-tag race with per-worker private tables mirrored from an append-only release-published log, and confirms matches by full-key comparison. Rollback is the selected official A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.
- Exact-source CI [41232109362](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41232109362) succeeded. Developer tests report seeds 1–3 exact, ASan/UBSan and TSan clean at 6 and 12 threads. On a 4-vCPU host, interleaved seed-1 full runs report 180→115 ms CPU and 52–60→36–39 ms wall; 12-worker cgroup peak 13–15 MB. These are developer measurements, not scoring-box axes.
- The exact source compiled locally with official `-O3 -march=x86-64-v3 -std=c++20 -DNDEBUG -pthread -static-libstdc++ -static-libgcc` flags. Official run `run-0e05ac922f25` on commit `8c51ca2873b18b633fce3f1772a3c6a1a6359b32` passed all five gates: T=0.020318 s, M=22,478,848 B, S=574, D=1, K=44.521760, points=82.428616. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).
- Versus the preceding selected A source run `run-3ba931887dae` (T=0.020080 s, M=20,897,792 B, S=584, K=45.325284), PR #2 is 1.2% slower, 7.6% higher memory and K is 1.8% lower, despite 10 fewer source lines. Not promoted; restore selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.


## Official rollback checkpoint `cf650cc` — A selected source confirmed

- Board run `run-1811c32b60e4` on commit `cf650cc6b47038ae06fdf208279d68e2c14355aa` passed all five gates on selected A champion blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017989 s, M=21,020,672 B, S=584, D=1, K=47.831019, points=83.985482. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). All four tracks on this dispatch were below their source-identical BESTs, so this repeat does not justify an A source change.

## A frontier PR #5 four-byte records — official trial queued

- Exact candidate source blob `ccf2219993e368f94cc507f1c2b83f046d45afb5` from draft PR #5 head `d595162bebd3999c57b7c5d6a2bb36051a1723a3`; selected-source rollback is parent blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`. Source size is 24,965 bytes / 676 physical lines versus 23,407 / 635 for A main; Docker and dependencies are unchanged.
- Exact-source CI [41293374325](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41293374325) passed full/sample/tiny hashes, seed-2/3 holdouts, reordered inputs, ASan/UBSan, TSan, pinned offline Docker, and 20,000-record/1,842-key latency escape checks. CI [41293612626](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41293612626) passed exactness and paired performance/memory studies. The two custom exactness suites were also run locally on the imported source.
- Three 31-run full-input matched trials against A main report candidate/main time ratios 0.9793, 0.9362, 0.9419; versus the certified lookup candidate ratios are 1.0299, 1.0014, 0.9980. Ten interleaved cgroup trials show median peak 5,765,120 B (sidecar), 6,096,896 B (main), and 6,291,456 B (certified map); sidecar maximum was 9,523,200 B. These are developer CI measurements, not official axes/K.
- The candidate is eligible for an official A scorer trial because the evidence supports a meaningful runtime/memory gain despite +41 physical lines. Board T/M/S/K and all gates are pending; do not promote until K exceeds BEST `run-118836ebd34c` (49.960098). Roll back to the parent-selected blob above if it does not.


## Official run `5f15f25` — selected A source

- Board run `run-f119f0ce2f4a` on commit `5f15f2543fbd6a9e18fc3f80490190399322a13d` passed all gates on A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.020173 s, M=21,606,400 B, S=584, D=1, K=44.920103, points=82.622037. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). A source is unchanged; compare this low repeat with other same-source readings rather than attributing it to code.

## A PR #5 official trial — candidate rejected, selected source restored

- Official run `run-864112d4e759` on commit `488ee43f787334f7c89060ebaaa785e069ea5982` passed all five board gates on exact PR #5 source blob `ccf2219993e368f94cc507f1c2b83f046d45afb5`: T=0.017171 s, M=21,147,648 B, S=621, D=1, K=48.449628, points=84.325792. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Candidate was 14.9% faster and 2.1% lower-memory than the immediately preceding selected-source run `run-f119f0ce2f4a`, but added 37 counted lines and did not beat BEST. Reject official promotion and restore selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; PR #5 remains unmerged.

## Official rollback `4b31a19` — A selected champion after PR #5 rejection

- Board run `run-751e772cabfa` on commit `4b31a195a1c7c4296ca7c3442e774fb9e3e59f91` passed all five gates after restoring selected A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`. T=0.019908 s, M=21,049,344 B, S=584, D=1, K=45.454924, points=82.879047. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Keep selected source; this is another noisy same-source repeat.

## Official C-main trial dispatch `5f00315`

- Board run `run-c3d414b0741e` on commit `5f00315f8696ca1853c5fb927ad5cd447c6253e9` passed all five gates on unchanged A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017672 s, M=22,147,072 B, S=584, D=1, K=47.756925, points=83.951818. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). No A source change.

## Official rollback `9ded4d1` — A selected champion after C trial

- Board run `run-c197a43f3f04` passed all gates on unchanged A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017183 s, M=21,430,272 B, S=584, D=1, K=48.751439, points=84.399372. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official evidence refresh `5d08af1`

- `run-293b0b1d57c9` passed all gates on unchanged A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017433 s, M=21,209,088 B, S=584, D=1, K=48.501146, points=84.287600. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official evidence refresh `89fb2f8`

- `run-f4fe824bcf20` passed all gates on unchanged A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017257 s, M=21,745,664 B, S=584, D=1, K=48.504863, points=84.289264. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Team-wide official evaluation `163279d` — unchanged A source

- Unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-0eb095ded2ce` passed all five gates, T=0.017515 s, M=21,512,192 B, S=584, D=1, K=48.250349. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). This same-source result is 7.1% above the immediately prior run `run-bc388b2bafe1` (K=45.038131), showing material board repeat variation.

## A frontier PR #6 small-group rank path — deferred without an official run

- Exact head `33e0f543fa9bbcd084954ab950a86d91d6b19495`; exact-source CI `41309800426` passed the reported seed-1 tiny/sample/full, seed-2/3, reordered-input, ASan/UBSan, TSan and offline-Docker checks. Two matched 31-run controls reported candidate/main runtime ratios 0.9828 (default), 0.9857 (1 thread), and 0.9863 (12 threads); memory.peak is noisy. The change adds 16 and removes 4 physical lines (+12 net), with no official K result. Defer dispatch: the sub-2% runner gain is small against source-size cost and board variance; reconsider with stronger paired memory/K evidence.

## Team-wide official evaluation `3a0273b` — unchanged A source

- Source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-006ae385f65c` passed all five gates, T=0.017297 s, M=21,135,360 B, S=584, D=1, K=48.725370. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Same-source run after `run-0eb095ded2ce` (K=48.250349) confirms that repeated board results move materially without source changes.

## Team-wide official evaluation `2ace33f` — unchanged A source

- Source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-223d1ec66553` passed all five gates, T=0.020346 s, M=21,569,536 B, S=584, D=1, K=44.743998. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## A PR #6 current-base official validation candidate

- Exact PR head `33e0f543fa9bbcd084954ab950a86d91d6b19495`; source blob `c8ec203b3460cf9073dce25c15e4b15bff7b222b`. It is two commits ahead and zero behind current A main. Exact-source CI `41309800426` passed.
- Candidate adds <=8-element AVX2 sorting and a 1–2 element rank fast path. CI reports 31 matched full-input runs at default/1/12 threads with candidate/base ratios 0.9828/0.9857/0.9863 and exact hashes, sanitizers, offline Docker. Net +12 lines and noisy memory make it a trial only; official board validation pending.
- Local compile passed under the official Docker compiler flags. Keep selected-source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` for rollback.

## A PR #6 official trial `96443e0` — no promotion

- Exact candidate blob `c8ec203b3460cf9073dce25c15e4b15bff7b222b`; run `run-5377b0bccf4a` passed all five gates: T=0.020820 s, M=20,877,312 B, S=594, D=1, K=44.407993, points=82.373057. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098) on selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.
- Versus immediately preceding selected-source run `run-e8a4888a6a5f` (K=44.241045), this is a +0.38% K change, with T +0.27%, M -3.8%, and S +10. This does not establish a stable improvement over board variance; restore selected source `c91b9689529c9c92472be91dbc36f0716e2c98e5` and leave PR #6 unmerged.

## Official A rollback verification `bfb66b` — latest

- Selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-a06a10b756c8` passed all five gates: T=0.019652 s, M=21,598,208 B, S=584, D=1, K=45.515105, points=82.907777. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official current-source confirmation `97de154` — latest

- Selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-8e61c8f82744` passed all five gates: T=0.019879 s, M=20,926,464 B, S=584, D=1, K=45.541364, points=82.920302. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official A source confirmation `0874d1c` — latest

- Selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-5245d92d586f` passed all five gates: T=0.020364 s, M=21,172,224 B, S=584, D=1, K=44.890829, points=82.607881. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official source confirmation `3e16ed7` — latest

- Selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-222209a4f06f` passed all five gates: T=0.020681 s, M=20,992,000 B, S=584, D=1, K=44.621682, points=82.477297. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official source confirmation `63f6eed` — latest

- Same selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-a631b5dc8e9f` passed all five gates: T=0.019848 s, M=21,184,512 B, S=584, D=1, K=45.465335, points=82.884020. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). This was a source-identical rerun; it does not validate a new candidate.

## Official source confirmation `f739ccb` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-98bbf85d2c4d` passed all five gates: T=0.017674 s, M=20,582,400 B, S=584, D=1, K=48.459155, points=84.268792. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `dbea191` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-3a2af9a35e69` passed all five gates: T=0.017723 s, M=21,241,856 B, S=584, D=1, K=48.087850, points=84.101768. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `ba05448` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-a2c499a817b5` passed all five gates: T=0.020247 s, M=21,483,520 B, S=584, D=1, K=44.889114, points=82.607052. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `142a9fd` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-bb3dc975ef65` passed all five gates: T=0.017524 s, M=21,794,816 B, S=584, D=1, K=48.112199, points=84.112760. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `9aaa62c` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-7bf23a604e9b` passed all five gates: T=0.020287 s, M=21,495,808 B, S=584, D=1, K=44.839710, points=82.583140. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `0a1e4cb` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-172f08cfcd5c` passed all five gates: T=0.020062 s, M=20,856,832 B, S=584, D=1, K=45.363409, points=82.835284. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not a new candidate.

## Official source confirmation `7e3b4b6` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-5708c2e8ce9e` passed all five gates: T=0.021118 s, M=20,701,184 B, S=584, D=1, K=44.280961, points=82.310852. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source-identical rerun, not an A candidate.

## Official source confirmation `7753f18` — latest

- Same source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: run `run-4730bfbf374c` passed all five gates: T=0.020033 s, M=20,979,712 B, S=584, D=1, K=45.342929, points=82.825478. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).


## A frontier PR #5 word4 sidecar — official rejection (2026-11-01)

- Candidate source blob `ccf2219993e368f94cc507f1c2b83f046d45afb5`; official run `run-544b9019d82f` on commit `c1c2c9fdd77044d39c4f433b0400aad1ed7c267a` passed check/build/correctness/timeout/sandbox. T=0.017305 s, M=20,832,256 B, S=621, D=1, K=48.406936, points=84.245380.
- BEST remains `run-118836ebd34c`, K=49.960098. Candidate K is 3.1% below BEST despite improving over the preceding LATEST (`run-e47f3c8496c1`, K=44.333801); added 37 counted source lines (S 584→621). Reject promotion and restore selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; leave PR #5 unmerged.


## A source rollback confirmation after PR #5 rejection (2026-11-01)

- Restored selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; run `run-21dd156e1528` on commit `0df4790f0becf12bb8935e6edc9470873d73c406` passed all gates: T=0.017494 s, M=21,393,408 B, S=584, D=1, K=48.332795. **BEST** remains `run-118836ebd34c`, K=49.960098.


## Selected-source rollback run after A #5 trial (2026-11-01)

- Official source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` was restored; run `run-ec273c5aec73` on commit `39bc3db91faaa25fcaf344a62c3f973ed6ff8a9e` passed all five gates: T=0.019947 s, M=21,524,480 B, S=584, D=1, K=45.208192. **BEST** remains `run-118836ebd34c`, K=49.960098. No A source promotion.


## Team-wide run during B main-source trial (2026-11-01)

- Unchanged selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; run `run-4a7eef6577b1` on commit `6cb6df52c71f607af145c164a40fef274eea3c95` passed all five gates: T=0.017386 s, M=21,557,248 B, S=584, D=1, K=48.408761. **BEST** remains `run-118836ebd34c`, K=49.960098.


## Exact current-head rerun after B source trial (2026-11-01)

- Unchanged selected A blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; `run-a7effc2ef04d` on `d90da4f39ac3c9cda07fbc7f57f816dc19976a25` passed all five gates: T=0.020444 s, M=20,971,520 B, S=584, D=1, K=44.888340. **BEST** remains `run-118836ebd34c`, K=49.960098.


## Exact current-head rerun 2026-11-01

- Selected source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; `run-0a532a51a6df` on `45e8a07f2baad5113c6b858e2d3576b6db29a436` passed all five gates: T=0.021185 s, M=21,118,976 B, S=584, D=1, K=44.034560. **BEST** remains `run-118836ebd34c`, K=49.960098.

## Exact current-head run after receipt update (2026-11-01)

- `run-59577f7ee2ab` on `f3e5fbd8ece8535c3142c8a914813075dddff341` passed all five gates: T=0.019918 s, M=21,188,608 B, S=584, D=1, K=45.383618, points=82.844956. **BEST** remains `run-118836ebd34c` (K=49.960098); this is **LATEST**.

## Frontier A PR #4 official trial (2026-11-01)

- Staged exact PR head `c6cc55f64f19bbfbfb28f726ac9874313ab9b3d2`; imported only its `track-a/main.cpp` (source blob `e2713339cf44e515783d8671b1db074904070e3b`), retaining the official Dockerfile and all other tracks. The exact-head developer workflow `41290978319` passed. The candidate certifies the endpoint fingerprint table only after all 1,842 catalogue endpoints have been seen; that count is specified for full/sample, while tiny never reaches the fast path. The test suite includes forced signature collisions and exact output checks.
- Developer paired local claim: 3–5% faster; not official score evidence. Official board T/M/S/D/K and correctness gates will determine promotion. Rollback is the immediately preceding A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.

- Official result `run-c9c269752506` on `18d16b927ac28c90205dbfe4934b5951f0cfea48`: all five gates passed; T=0.019821 s, M=20,615,168 B, S=607, D=1, K=45.480574, points=82.891297. It is 0.21% above the prior same-source/other-track run `run-59577f7ee2ab` (K=45.383618), but below A **BEST** `run-118836ebd34c` (K=49.960098), and S increased 23 lines. Do not promote this candidate.

## Frontier A PR #6 official trial (2026-11-01)

- Staged exact PR head `33e0f543fa9bbcd084954ab950a86d91d6b19495`; imported only `track-a/main.cpp`, source blob `c8ec203b3460cf9073dce25c15e4b15bff7b222b`, retaining the official Dockerfile. Exact-head CI `41309800426` passed all listed correctness, sanitizer, Docker and performance checks. Its 31-run matched local medians showed 0.9828x runtime at default threads, 0.9857x at one thread, and 0.9863x at twelve threads; these are developer-box measurements, not official score evidence. Rollback is known-good A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`.

- Official result `run-d8a21881b2e1` on commit `b098465d9c206e5f25fe2ccb1996689a1d676302`: all five gates passed; T=0.019519 s, M=24,281,088 B, S=594, D=1, K=44.499386, points=82.417701. Versus the immediately preceding A source result `run-59577f7ee2ab` (K=45.383618), T was 2.0% lower but M was 14.6% higher, S grew by 10, and K fell 1.95%. This does not beat A **BEST** `run-118836ebd34c` (K=49.960098); reject PR #6 and restore the known-good source.

## Restored A source exact-head rerun (2026-11-01)

- Restored source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; `run-1d61396945dc` on commit `f8e388471260b59810b9974252b8a5d8bfe8d5ec` passed all five gates: T=0.019800 s, M=21,151,744 B, S=584, D=1, K=45.534507, points=82.917032. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

- Unchanged source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; `run-7acef862a9d8` on commit `ab84ec24be844316a3a88a8e8ad2edaca5824e88` passed all five gates: T=0.020491 s, M=21,557,248 B, S=584, D=1, K=44.590488, points=82.462111. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — 2026-11-01, commit `9dcde1dd1cedf6e421c55f8bb29b66a8c31544fa`

- **LATEST:** `run-142724155992`; T=0.021338 s, M=20,996,096 bytes, S=584, D=1, K=43.927643, points=82.136895; check/build/correctness/timeout/sandbox gates all passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -12.07% versus BEST. Versus prior receipt `run-1d61396945dc` (K=45.534507), latest K changed -3.53%.
- Source snapshot: A `c91` / B `b8ef` / C `0772` / D `b7`. No source promotion or PR merge from this run.

## Official board receipt — 2026-11-01, commit `d04c1c7fac73ba0b433fc978ca17ea73ba15a6ff`

- **LATEST:** `run-b94a33c52541`; T=0.017905 s, M=21,635,072 bytes, S=584, D=1, K=47.667638, points=83.911182; check/build/correctness/timeout/sandbox gates all passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -4.59% versus BEST. Against preceding same-source receipt `run-142724155992` (K=43.927643), K changed +8.51%; these measurements do not support a source promotion.
- Sources unchanged: A `c91` / B `b8ef` / C `0772` / D `b7`; no PR merged.

## Official board receipt — 2026-11-01, commit `542794bc00d4d346b65976f073a5f2cf1ec22593`

- **LATEST:** `run-41276f576b63`; T=0.020007 s, M=21,241,856 bytes, S=584, D=1, K=45.259837, points=82.785649; all five gates passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -9.41% versus BEST. Against preceding same-source run `run-b94a33c52541` (K=47.667638), K changed -5.05%; source unchanged.
- No source promotion or PR merge is supported by this run.

## Official board receipt — 2026-11-01, commit `269e0bb26368cb0d38f492561d8f11ab8b47a131`

- **LATEST:** `run-e2e93406576d`; T=0.017889 s, M=21,000,192 bytes, S=584, D=1, K=47.973873, points=84.050239; all five gates passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -3.98% versus BEST. Against preceding same-source run `run-41276f576b63` (K=45.259837), K changed +6.00%; source unchanged.
- No source promotion or PR merge is supported by this run.

## Official board receipt — 2026-11-01, commit `33914daf6197af1b5f3fbf564accbbf217b9b882`

- **LATEST:** `run-e1636100f54c`; T=0.020625 s, M=21,139,456 bytes, S=584, D=1, K=44.619708, points=82.476336; all five gates passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -10.69% versus BEST. Against preceding same-source run `run-e2e93406576d` (K=47.973873), K changed -6.99%; source unchanged.
- This source-identical rerun does not support promoting an open candidate.

## Official board receipt — 2026-11-01, commit `c97e128f086a883ce4a9b6287e345e6fce3b9565`

- **LATEST:** `run-b71814a3d1e1`; T=0.020500 s, M=21,196,800 bytes, S=584, D=1, K=44.731296, points=82.530574; all five gates passed.
- **BEST remains:** `run-118836ebd34c`, K=49.960098; latest K is -10.47% versus BEST. Against preceding same-source run `run-e1636100f54c` (K=44.619708), K changed +0.25%.
- This source-identical rerun provides no promotion evidence.

## Frontier candidate trial — sd-ta PR #7 (2026-11-01)

- Imported only `track-a/main.cpp` from PR HEAD `40a276405ea594f2f98d2e52912d66c84e3885e9`; source blob verified as `1ad533f716e9f898eeb0e174959bfb25cad52e85`. The PR's research artifacts and workflow edits were not imported. Prior A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` remains in the preceding submission commit for rollback.
- Official baseline before this trial: `run-d5c85d097f0d` on source `c91b9689`, T=0.020231 s, M=20,791,296 B, S=584, D=1, K=45.201982, points=82.757874; all five gates passed. A BEST remains `run-118836ebd34c`, K=49.960098.
- Exact candidate source blob `1ad533f7` is present on CI-tested commits `1961c148d35cc3a8114b68a5153dda8b271f447d` and `27a8927f4a80bca0ac5c009be3f02b505c137152`; CI runs [41332666362](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41332666362) and [41333014119](https://github.com/insightlabs38-pixel/sd-ta/actions/runs/41333014119) both succeeded. Developer qualification reports exact hashes, differential/adversarial CRC-collision cases, strict ASan/UBSan and TSan, and restricted Docker.
- Developer paired pinned-Docker evidence reports candidate/champion 12-worker T ratios 0.9474/0.9489 and M ratios 0.8877/0.8441; S=578 (six fewer lines), D=1. Projected K≈52.65/53.14 is developer analysis only, not an official result.
- Official trial: `run-786c2c61128b` passed all five gates: T=0.017286 s, M=21,168,128 B, S=578, D=1, K=48.801309, points=84.421574. This is +7.96% K versus the immediately prior same-source run `run-d5c85d097f0d` (K=45.201982), but -2.32% versus the recorded A BEST `run-118836ebd34c` (K=49.960098); T is slower than BEST. **Decision: not promoted.** Restored source blob `c91b9689`; PR #7 stays open and unmerged.

## Official board receipt — A PR #7 trial, commit `65ac364be8965ab62a3ba737882b630a4bb126ae`

- `run-786c2c61128b`: T=0.017286 s, M=21,168,128 B, S=578, D=1, K=48.801309, points=84.421574; all gates passed. It did not beat BEST; see the PR #7 decision above.

## Official board receipt — A champion rollback, commit `cffcacbe03237196298ec5c5e302392ec24f865d`

- **LATEST:** `run-b5fb88b93835`; T=0.017847 s, M=21,606,400 B, S=584, D=1, K=47.757697, points=83.952169; all five gates passed. **BEST remains** `run-118836ebd34c`, K=49.960098.

## Official board receipt — D batch-size trial, commit `5b45d276d3f038daebbf8c290ea021507086b456`

- `run-7a9147aaad6f` (A source c91): T=0.020975 s, M=20,762,624 B, S=584, D=1, K=44.405323, points=82.371752; all five gates passed. **BEST** remains `run-118836ebd34c`, K=49.960098.

## Official board receipt — rollback checkpoint `cdd6fd395d013eb19d3bd2ff7917c4e1ceea50e9`

- `run-dc9a79f89aea` passed all five board gates: T=0.017094 s, M=20,910,080 B, S=584, D=1, K=49.118996, points=84.562474. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Source is the known-good Track A blob `c91e89f79c1c6a9bbaf0121b75103ec2f6e39cf4`.

## Official board receipt — B row-prefetch trial, commit `aac3a059e93d5b8b31ea9cef2b1522398ef6b593`

- `run-7475f872e70f` passed all five gates: T=0.020448 s, M=20,545,536 B, S=584, D=1, K=45.068547, points=82.693678. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — Track B restored-source comparison, commit `f00fe1077308e74fbf82bc75a3cb311502de4a7c`

- `run-c8f1c034131f` passed all five gates: T=0.016847 s, M=20,893,696 B, S=584, D=1, K=49.485518, points=84.723906. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — Track B row-prefetch confirmation, commit `b6f4226481a9adf8d9dbddcac3f6d67593de62c3`

- `run-de6e21f6d42c` passed all five gates: T=0.019586 s, M=21,266,432 B, S=584, D=1, K=45.733103, points=83.011533. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — Track B champion rollback, commit `021d3bbbbb502e762e7402f38ff341f67bccd377`

- `run-6afbd0fd73d5` passed all five gates: T=0.022074 s, M=21,192,704 B, S=584, D=1, K=43.108675, points=81.728234. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — pre-D-PR #15 baseline, commit `c0bce0d013a45775ce9d470f0c33b774a28fc0a2`

- `run-29002e5ece10` passed all five gates: T=0.021420 s, M=21,274,624 B, S=584, D=1, K=43.728075, points=82.038018. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — D PR #15 BATCH=32 trial, commit `fb66a3774da75cd6cbe47b6b6a3f90d4eba930ca`

- `run-094041182b00` passed all five gates: T=0.018050 s, M=21,524,480 B, S=584, D=1, K=47.524475, points=83.845867. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — D PR #15 BATCH=8 trial, commit `eb21daa231bb1bddad8c277f186cd516c05025d4`

- `run-bc6beaac8fde` passed all five gates: T=0.021645 s, M=21,147,648 B, S=584, D=1, K=43.552316, points=81.950563. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official board receipt — D promotion checkpoint, commit `650272f4043d367210da65af1ca0d8f07f640f5f`

- `run-bf05c8526c39` passed all five gates: T=0.021171 s, M=20,631,552 B, S=584, D=1, K=44.255311, points=82.298270. A source unchanged; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official trial — frontier PR #5 four-byte records with overflow sidecar

- Candidate is the exact `track-a/main.cpp` blob `ccf2219993e368f94cc507f1c2b83f046d45afb5` from `sd-ta` PR #5 head `d595162bebd3999c57b7c5d6a2bb36051a1723a3`. It packs common-case request records into 32-bit words and resolves the reserved latency sentinel through a lossless per-run overflow sidecar.
- Exact-source CI run `41293374325` passed reference hashes, reordered/synthetic exactness including full `uint32` boundary cases, ASan/UBSan, TSan, and pinned offline Docker. Memory/axis CI `41293612626` used the identical source blob and passed.
- Developer paired pinned-Docker measurements (not board scores): candidate/current-main runtime ratios across three independent CI runs were `0.9793`, `0.9362`, `0.9419`; candidate/certified-lookup ratios were `1.0299`, `1.0014`, `0.9980`. Ten interleaved cgroup peak-memory measurements had medians: main `6,096,896 B`, certified lookup `6,291,456 B`, candidate `5,765,120 B` (candidate −5.44% vs main). These are runner measurements, not official K/M.
- Source changes from the current A champion are +41 formatted lines (+1,558 bytes); the official size/runtime/memory axes must decide whether the speed and memory evidence outweigh this.
- **Pretrial BEST:** `run-118836ebd34c`, K=`49.960098`. **Rollback:** parent official commit source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`. Await the official all-track result before promoting/merging PR #5 or reverting.

## Official board trial — A frontier PR #5 sidecar result (commit `54b423edcac810adb53fb4c746152dc356296984`)

- `run-60f196a29e66` passed all five gates: T=`0.017455 s`, M=`20,709,376 B`, S=`621`, D=1, K=`48.255556`, points=`84.177366`.
- Against pretrial BEST `run-118836ebd34c` (T=`0.016388 s`, M=`21,344,256 B`, S=`584`, K=`49.960098`), this exact PR #5 source was +6.51% T, −2.97% M, +37 S, and −3.41% K. **Reject promotion**; retain the known-good source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` from rollback checkpoint `1db8a8f00a20efb3107ee843ced783fa5de32b0a`. PR #5 remains open/draft.

## Official board trial — A frontier PR #4 catalog certificate (pending)

- Exact candidate source blob `e2713339cf44e515783d8671b1db074904070e3b` from `sd-ta` PR #4 head `c6cc55f64f19bbfbfb28f726ac9874313ab9b3d2`; it uses an exact endpoint-catalog saturation certificate after all 1,842 specified keys have appeared, retaining full byte comparisons for collisions. Current organizer spec `specs/a-ingest.md` (main `9f059f75384607c7836997063b0901b98f36b5fa`) specifies exactly 1,842 endpoints in full/sample; tiny is a subset.
- Exact-head verification run `41290978319` and paired current-main run `41290905376` passed. Two independent 31-run complete-program comparisons reported candidate/current-main runtime ratios: 1-thread `0.9733` / `0.9667`; 4-thread `0.9582` / `0.9501`; 12-thread `0.9612` / `0.9730`. Forced signature-collision and saturation tests are included. These are developer-runner timings, not official T/K/M.
- Official result `run-21ad666f505a` passed all five gates: T=`0.019427 s`, M=`21,843,968 B`, S=`607`, D=1, K=`45.410566`, points=`82.857846`. Against BEST `run-118836ebd34c` (K=`49.960098`), this was +18.54% T, +2.34% M, +23 S, −9.11% K; the local speed gain did not transfer. **Reject promotion; PR #4 remains draft.**

## Official board trial — A frontier PR #6 small-group percentile fast path (rejected)

- Candidate source blob `c8ec203b3460cf9073dce25c15e4b15bff7b222b` from `sd-ta` PR #6 head `33e0f543fa9bbcd084954ab950a86d91d6b19495`; exact CI `41309800426` passed seed/reference, reorder, ASan/UBSan, TSan, and offline Docker gates. It adds an exact rank fast path for n≤2 and a single AVX2 network for n≤8.
- Matched 31-run local medians vs current main: candidate/main runtime ratios `0.9828` default, `0.9857` one thread, `0.9863` 12 threads. Memory was noisy and no official K claim is made. Source is +12 formatted lines (+381 bytes). Official result on `32a2c5f2192e5ead9bc480c1392f6dc2a741cee2`: `run-b1fd0c119d83` passed all five gates with T=0.018093 s, M=21,286,912 B, S=594, K=47.452446, points=83.812930. Relative to BEST `run-118836ebd34c` (K=49.960098), K is 5.02% lower. Reject promotion; keep rollback source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` from commit `1db8a8f00a20efb3107ee843ced783fa5de32b0a`.


## Official all-track receipt — A PR #6 trial, commit `32a2c5f2192e5ead9bc480c1392f6dc2a741cee2`

- `run-b1fd0c119d83` passed all five gates: T=0.018093 s, M=21,286,912 B, S=594, D=1, K=47.452446, points=83.812930. **LATEST** for the trial; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official A frontier trial — PR #7 compact hourly results and shared exact dictionary (rejected)

- Exact source blob `1ad533f716e9f898eeb0e174959bfb25cad52e85`, from PR #7 head `40a276405ea594f2f98d2e52912d66c84e3885e9`; this is a compact numeric hour queue, early run-buffer recycling, and a shared immutable endpoint table with full-byte equality. Only the source and its updated local README are staged for official scoring.
- Exact-source CI runs `41332666362` and `41333014119` passed reference/hash, arbitrary-order and 1,842-way colliding-fingerprint tests, ASan/UBSan, TSan and restricted pinned-Docker checks. Two independent pinned-Docker qualifications reported 12-worker candidate/champion timing ratios 0.9474 and 0.9489 and cgroup peak-memory ratios 0.8877 and 0.8441. PR reports S=578 and D=1; these are developer qualification results, not board measurements. Its projected K≈52.65–53.14 is a projection only.
- Host GCC 14 compile with the official optimization flags succeeded. Local pinned GCC 15 Docker build could not unpack its compiler image because the execution environment reported no space in its Docker layer store; exact-source CI used the pinned toolchain successfully.
- Official result `run-412840bb86ca` on commit `81943ddb059636a4ae357613c0a887beb688e7db` passed all five gates: T=0.020755 s, M=20,717,568 B, S=578, D=1, K=44.728681, points=82.529305. Relative to BEST `run-118836ebd34c` (K=49.960098), T regressed 26.65%, M fell 2.94%, S fell by 6, and K fell 10.47%. The projected K gain and paired local timings did not carry to the official build. Reject promotion; restore exact A main source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; do not merge PR #7.


## Official all-track receipt — A PR #7 trial, commit `81943ddb059636a4ae357613c0a887beb688e7db`

- `run-412840bb86ca` passed all five gates: T=0.020755 s, M=20,717,568 B, S=578, D=1, K=44.728681, points=82.529305. **LATEST** for the trial; **BEST** remains `run-118836ebd34c` (K=49.960098).


## Official all-track receipt — C main trial, commit `b9012e5073ea49c8f6e39079bfc43b4953eb6b2b`

- `run-a2f8916c6b98` passed all five gates on restored A champion blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.020123 s, M=21,508,096 B, S=584, D=1, K=45.016913, points=82.668786. **LATEST** for unchanged source; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — restored selected tree, commit `199e41df4695b591c909b064af49fb80ecd1388b`

- `run-3d97ca0b093f` passed build, check, correctness, timeout, and sandbox gates: T=0.017351 s, M=22,007,808 B, S=584, D=1, K=48.257504, points=84.178243. A source remained selected blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`; LATEST is this run. BEST remains `run-118836ebd34c` (K=49.960098); this result is 3.41% below BEST.

## Official all-track receipt — evidence checkpoint `d70ce847a8dbef1a2881a017207d5ecb4f520d9f`

- `run-7cb70fc3080d` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017517 s, M=21,282,816 B, S=584, D=1, K=48.351147, points=84.220339. **LATEST** is this run; **BEST** remains `run-118836ebd34c` (K=49.960098), 3.22% higher.

## Official all-track receipt — checkpoint `2470b6250a0cd834661b1ca5b21def7b4703ef50`

- `run-6ed2d5bff9c8` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.021272 s, M=21,303,296 B, S=584, D=1, K=43.868112, points=82.107447. **LATEST** is this run; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — checkpoint `19582b89b83bb4bdc46998fdbcd9c7d0fb7baadd`

- `run-db050f90d048` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.020287 s, M=21,291,008 B, S=584, D=1, K=44.925644, points=82.624715. **LATEST** is this run; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D PR #18 trial, commit `bc7dcf4d5ec5f0a9da9db0018c83a89f712c38d0`

- Unchanged selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` passed all five gates in `run-44fb00e3cc22`: T=0.019750 s, M=20,934,656 B, S=584, D=1, K=45.686275, points=82.989288. **LATEST** is this run; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D PR #17 trial, commit `e41565497e22f570dab2474001b8460272024f78`

- Unchanged selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` passed all five gates in `run-11f27b2663f4`: T=0.019726 s, M=21,442,560 B, S=584, D=1, K=45.495414, points=82.898381. **LATEST** is this run; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D PR #17 repeat, commit `648afc7992a40d79ead4e56abe7abe56d310017a`

- Unchanged selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5` passed all five gates in `run-43aa8ea8be21`: T=0.019535 s, M=21,508,096 B, S=584, D=1, K=45.689391, points=82.990768. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D main cap-4 comparison, commit `27d732ecd32dcda88f7e2dd00e2bfc1ba08e3477`

- `run-eb3472268bfd` passed all five gates on unchanged selected A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.019879 s, M=21,577,728 B, S=584, D=1, K=45.263075, points=82.787203. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — restored D PR #17, commit `a2c7057b631abd61ed3618f7a8f621fa69b3f3ea`

- `run-eb22df8eb60f` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.017240 s, M=21,712,896 B, S=584, D=1, K=48.543411, points=84.306514. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — run-log checkpoint `770ff3ed22aef6d4cb07026aa0a07e2c3ded7911`

- `run-3fffe8f03f0d` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.018406 s, M=21,377,024 B, S=584, D=1, K=47.127381, points=83.663665. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D README/performance-log checkpoint `5e2c127efce867d05e8bee41d20d5b7f0a058d21`

- `run-585cb7c424af` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.020957 s, M=20,930,560 B, S=584, D=1, K=44.352871, points=82.346087. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).

## Official all-track receipt — D PR #17 outcome checkpoint `128993129f41ea3cc850aaadcfccf1f4a3b8f791`

- `run-e6eddbee1577` passed all five gates on unchanged A source blob `c91b9689529c9c92472be91dbc36f0716e2c98e5`: T=0.020639 s, M=21,467,136 B, S=584, D=1, K=44.467562, points=82.402166. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098).


## Official all-track receipt — D PR #19 trial commit `798c15d26ee3132bbc5d29541ee3d1de2534839a`

- `run-da07f2b68c90` passed all five gates: T=0.017783 s, M=21,491,712 B, S=584, D=1, K=47.894512. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). This is a cross-track rerun while testing D PR #19; no A source changed.


## Official all-track receipt — D PR #19 repeated trial commit `2d6609b2d6a26f79b20b3df8a5dc2dbd9fa6f7e6`

- `run-fe94a5b4bcea` passed all five gates: T=0.020431 s, M=21,475,328 B, S=584, D=1, K=44.689932, points=82.510485. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Cross-track rerun only; A source unchanged.


## Official all-track receipt — D PR #20 trial commit `a8ff46e16509338f515a4569f0de934e175825a5`

- `run-2d5328044576` passed all five gates: T=0.021565 s, M=20,819,968 B, S=584, D=1, K=43.769514, points=82.058586. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Cross-track rerun only; A source unchanged.


## Official all-track receipt — D PR #23 combined traversal trial commit `a5b6172a946ed30ffc912ea7e2c09474851e6768`

- `run-315569e77f7b` passed all five gates: T=0.020446 s, M=21,434,368 B, S=584, D=1, K=44.690597, points=82.510808. **LATEST**; **BEST** remains `run-118836ebd34c` (K=49.960098). Cross-track rerun only; A source unchanged.

## Official latest run — commit `56f3cabeab3c780111683a9b9f67e6b54dc824b9`

`run-0ac459f91a88` passed check/build/correctness/timeout/sandbox: K=44.776815, T=0.020327 s, M=21,540,864 B, S=584, D=1, points=82.552660. BEST remains `run-118836ebd34c` (K=49.960098). Track A source was unchanged; this is a new baseline observation, not an A candidate promotion.

## Official champion-restoration run — `8fc0d908aeadb934648e44e70f1e0dcd1b35173f`

`run-64771385ab4c` passed all five gates: K=44.543790, T=0.020492 s, M=21,667,840 B, S=584, D=1, points=82.439358. BEST remains `run-118836ebd34c` (K=49.960098). Source unchanged; compare with PR #22 trial `run-0ac459f91a88` only as a noisy repeat, not an A change.

## Official receipt-checkpoint run — `75376b0a3d67c033a4b12d4d950b68b503c4921e`

`run-ea1cfb55cc8d` passed all five gates: K=48.788061, T=0.017038 s, M=21,807,104 B, S=584, D=1. BEST remains `run-118836ebd34c` (K=49.960098); source unchanged.

## Official latest run — `36ce0278de8128b5ebacad3fd88fc60da4dec86d`

`run-a1c1177b8dd8` passed all five gates: K=48.531104, T=0.017267 s, M=21,655,552 B, S=584, D=1. BEST remains `run-118836ebd34c` (K=49.960098); source unchanged.

## Official latest run — `73c861213ac0e54ce07f817e0e9daa3c51b70d04`

`run-39833bd0f9e5` passed all five gates: K=42.657890, T=0.021605 s, M=23,568,384 B, S=584, D=1. LATEST only; BEST remains `run-118836ebd34c` (K=49.960098). No source changed; treat as a noisy run.
