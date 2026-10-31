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
