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
