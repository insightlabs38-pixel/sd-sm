# Track B: performance log

The independent development repository is not the official submission. Board run IDs and official K values must be recorded by the official integrator after verified promotions.

| Step | Change | Board run ID | T (s) | M (MB) | Points |
|---|---|---|---|---|---|
| 0 | Organizer Python reference | Not submitted here | 56.35 | 2,200 | Not measured here |
| 1 | Selective postings plus token-ID tape, exact phrase verification | Pending official run | Pending | Pending | Pending |
| 2 | Shared deduplicated token automaton for high-frequency phrases | Pending official run | Pending | Pending | Pending |

## Local, non-scoring evidence (synthetic inputs)

On the same in-chat Linux host and 100,000-document/20,000-query synthetic workload (75,307,568 input document bytes), baseline wall time was 22.97 s and peak RSS 205,608 KiB. The automaton variant took 3.05 s and peak RSS 206,108 KiB, with identical SHA-256 output (`ebe9a652d36670f1fa07f61a0e0121dbdac27c34cc289ab4ec86418f8abb097a`). This is a 7.53x local speedup on this synthetic workload, not an organizer benchmark.

On a separate 250,000-document/50,000-query synthetic workload (188,596,118 document bytes), the initial automaton crossover took 12.81 s with peak RSS 505,532 KiB. A measured 500-document posting threshold improved this to 6.90 s with peak RSS 509,272 KiB on the same input and identical SHA-256. These inputs differ from the official generator and must not be used as official scores.

The 500-document crossover also reduced the 100,000-document synthetic workload to 2.74 s with 206,400 KiB peak RSS, again retaining the exact prior output digest. Threshold sweeps on the 250,000-document synthetic input measured 7.22 s at 0, 7.42 s at 250, 6.80 s at 500 and 10.95 s at 1,000; these are host-local timings, not board scores, and the chosen threshold remains subject to official-corpus verification.

## Luna integration validation, October 30, 2026

- Candidate source: `sd-tb` HEAD `f5a81b9` (includes the common-phrase automaton). Previous official Track B candidate remains in parent commit `f100d67b58f81ca3ebec4833bb4337a0e0893f04` for rollback.
- Official seed-1 full, sample, and tiny outputs, plus seed-2 sample, match the organizer reference exactly. The independent differential suite passed seven random seeds, the worked example, and common-phrase/duplicate/suffix cases.
- Official Dockerfile check passed. Offline build produced an 81 MB image. Full seed-1 sandbox check passed with expected SHA-256 `f86973c210228141bcb6f1f1b10188ad2a9b65f71e7cd7cf4590b38de4e80927`.
- Local full-seed-1 check time including startup improved from 17.43 s to 15.67 s (about 10.1%); local cgroup peak was 420,638,720 bytes versus 420,597,760 bytes for the baseline. These are local measurements, not scoring-box results.
- Board run IDs: none; registration is pending. No official score claimed.

## Additional developer CI evidence, October 30, 2026

- Developer GitHub Actions sweep [run 41082239158](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41082239158) passed exact full seed-1 published SHA and full seed-2 byte comparisons for each of six crossover thresholds. This was a GitHub-hosted runner, not the scoring system; these values are not official board T/M/K and the run ID is not a board run ID.
- Two-repeat means for thresholds 0/100/250/500/1000/1250 were respectively 8.48/8.25/7.14/7.31/7.61/7.19 s on seed 1, and 7.88/7.82/7.44/7.91/7.22/7.47 s on seed 2. Peak RSS ranged approximately 653–661 MiB. Threshold 250 had the lowest two-seed mean (7.29 s); current code remains at the developer-verified threshold 500 pending a stable follow-up measurement and developer handoff. The sweep script and exact source are in `sd-tb` run 41082239158.
- Exactness CI run [41081539702](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41081539702) also passed the published sample/full hashes, sample seeds 2/3, seven deterministic differential seeds, and the offline pinned Docker gate. Its single-runner timings (sample 0.21 s/66,908 KiB; full 5.57 s/661,156 KiB) are not board results or official T/M/K.

## Promoted current verified B main candidate, October 30, 2026

- Promoted `sd-tb` main HEAD `2b765231755ad4e1645280276ff7f46fc91cf172`; production source blob `68bc2544bd842de00269c5797b7e33cb44cd6f54` combines the collision-safe 32-bit flat dictionary, verified final-AND anchor, and direct AC root transitions. The preceding official B candidate remains in parent `5f9e356c43e9ad613b75dd0a5c6b6c0376f2e39d` for rollback.
- Independent native checks matched official full seed-1 SHA-256 `f86973c210228141bcb6f1f1b10188ad2a9b65f71e7cd7cf4590b38de4e80927` (6.21 s on this local host) and sample seed-2 SHA-256 `86b92e3ceda664396bad5cabc3809b447de0610282eee484605fd23cbd12fea6`.
- Paired GitHub runner comparison [41087839664](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41087839664): direct AC root transitions reduced mean full-seed time 11.5% on seed 1 and 12.5% on seed 2 versus the prior verified candidate, with similar peak RSS (~662/654 MiB). Both seeds matched the organizer hash/reference.
- Exactness and Docker run [41088755772](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41088755772) passed seven differential seeds, official full/sample hashes, sample seeds 2/3, and offline Docker execution as an unprivileged user. The production source blob was `68bc254`.
- All timings above are local/GitHub-runner measurements, not board results. No official board run ID or K score exists.

## Verified parallel indexing and ordered query evaluation, October 30, 2026

- Integrated `sd-tb` main HEAD `fb7a21b1d3c53826cfe641290f40af5f8c21c63f`; production source blob `39a95d7409c8fcccdf65c99a0ff1a7ad2030077c`. This adds deterministic four-worker query evaluation to the previously verified parallel corpus index. The preceding serial-query/parallel-index candidate remains in official commit `4f38bf4` for rollback.
- Local native full seed-1 output matched the published SHA-256 `f86973c210228141bcb6f1f1b10188ad2a9b65f71e7cd7cf4590b38de4e80927`; sample seed-1 matched `eeeec1e9319da98a6f3c664c78f93e7078fd603c25c2bb3027174e81e3638a8f`.
- Paired developer runner comparison [41090220430](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41090220430) produced exact outputs for both full seeds. Median time fell from 2.52 to 1.74 s on seed 1 and from 2.35 to 1.74 s on seed 2 (31% and 26%); peak RSS remained about 766/764 MiB. These are developer-runner measurements, not board results.
- No official board run ID or K score exists. The preceding verified candidate remains the rollback point; no live score is claimed.


## Parallel phrase scans and selective Boolean/phrase evaluation, October 30, 2026

- Integrated `sd-tb` main HEAD `83308043a04cab19d8933e1b172b4cd05ee8ee6f`, production source blob `f036ae8927aaa24342e8e9a0ca9b6fb5301743f9`. This adds parallel document-range Aho-Corasick scans, rare-token phrase anchoring and adaptive intersection for highly unbalanced posting lists. The prior official source remains in commit `fb2e1fc` for rollback.
- Two independent full-seed comparisons [41093166652](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41093166652) and [41094072407](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41094072407) passed exact seed-1/2 outputs, differential checks and pinned offline Docker gates. Across the reported runs, mean full-seed time fell about 3.7% versus the prior parallel-index/query candidate; runner peak RSS stayed near 764–766 MiB. These are GitHub-hosted-runner measurements, not board T/M/K.
- Source grew by 44 nonblank lines in the developer comparison; runtime dependencies remain zero. The measured, repeatable runtime improvement is modest and the larger source cost should be included in final K assessment.
- Exactness/Docker run [41095024159](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41095024159) and ASan/UBSan/TSan run [41094997130](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41094997130) passed on code-identical source blob `f036ae8`. No official board run ID or K score exists.

## Branchless ASCII classification promotion, October 30, 2026

- Candidate `sd-tb` main HEAD `8a3856e1b24867b8fa88174352bae0402fafa5aa`, production source blob `77afbb2740358a9c137b412ef2af223b3fcc0e27`; previous official B source remains in release parent `00838f7` for rollback.
- The branchless token-byte predicate was exhaustively checked against the original classifier for all 256 byte values. Production-flag paired run [41097913555](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41097913555) matched full seed-1/2 outputs: 1.783 to 1.747 s (2.1%) and 1.797 to 1.777 s (1.1%), with peak RSS about 766/764 MiB. These are GitHub runner measurements, not board values. Exactness and restricted offline Docker passed in [41098792365](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41098792365).
- Compact vector AC experiment [41096477703](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41096477703) was not promoted because it showed no reliable speed or memory gain. No official board run ID or score is available.

## Fused corpus-token fingerprint, October 30, 2026

- Candidate: `sd-tb` main HEAD `0edb62fae10ebbf741db7ddb5c40af48e8d3cb11`, production source blob `1492bb104bc2825411d69b48dd56709d5423adc1`. The exact source blob matches the CI-generated `or` variant. Previous official release `1c235c35cc93ea146cf794254eecd56fab8f9948` remains available for rollback.
- Full-seed comparison [41109851588](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41109851588) passed seven differential seeds, collision cases, full seed 1 published hash, full seed 2 reference comparison and offline pinned Docker sample execution as uid 65534 with read-only root. Three-run means: seed 1 1.400 to 1.337 s (4.5% faster); seed 2 1.437 to 1.390 s (3.2% faster). Peak RSS stayed around 766/764 MiB. These are GitHub runner results, not board results.
- The scan now computes the query-visible token fingerprint while reading each token, avoiding a second byte scan. Source grew by 12 physical lines; no new runtime dependency.
- Official board BEST/LATEST: unavailable; the team has no registration entry and no board run IDs exist. No official score is claimed.

## Integrator qualification: compact query dictionary (October 30, 2026)

- Imported developer `sd-tb` source from `main` HEAD `a40baadb378f2c93a8ee4368ec292c85101cc96f`; production source blob `505fa18787f55c72c0c14dcdd403be585b855d48`. The top commit adds an isolated 16-bit tape experiment only; it is not included in this submission. Previous official source is recoverable from submission commit `34dee9b16ab17362b12e75289151a0a9750b2cb8` (blob `1492bb104bc2825411d69b48dd56709d5423adc1`).
- Developer qualification `41116820675` passed seven deterministic differential seeds, hash-collision and phrase cases, full seed-1 expected hash, full seed-2/3 independent Python references, restricted offline Docker, and ASan/UBSan. Three-run mean full times: seed 1 1.860 to 1.550 s (16.7% lower), seed 2 1.863 to 1.653 s (11.3% lower), seed 3 1.817 to 1.583 s (12.8% lower); peak RSS decreased about 3 MiB. These are GitHub-runner measurements, not board scores.
- BEST/LATEST official board result: none; no board score or run ID is claimed. Commit `34dee9b16ab17362b12e75289151a0a9750b2cb8` preserves the prior champion for rollback.

## Current developer candidate review — October 30, 2026

- Developer `main` HEAD `9f2286a83c131b8f3bca89d06eb27940cefd612b`, source blob `dc2ceedad12a72007d225c6d85566122b534ef36`, passed eight differential seeds, collision and phrase cases, two full-seed exact comparisons, and pinned offline Docker in CI [41138170073]. The paired three-run medians were 1.42 to 1.40 s (seed 1) and 1.42 to 1.41 s (seed 2); peak RSS was unchanged within measurement resolution. The source adds 31 physical lines. Using latest official T/M/S/D and a conservative S estimate, estimated K is flat to slightly lower; keep the scored source. The verified tape/cache alternatives that regressed are documented above.

## Official board receipts — raw-feed snapshot 2026-10-30 22:52:25 UTC

HighVelocity (`highvelocity-7f330e`) is registered. The watcher reported submission HEAD `3059e71b54cd02e920e995d186a369b4be9c0aeb`, healthy, with no queued or in-flight run at this snapshot. BEST and LATEST are both this successful live-board run; build, check, correctness, sandbox, and timeout gates all passed. These are board IDs, not CI IDs. Earlier “no board run/registration” notes are historical and superseded here.

- **BEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.
- **LATEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.


## Official board receipts — raw-feed snapshot 2026-10-30 22:58:54 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher was healthy at `40847ba5fde8714895533f7b47ce8fee48baa09e`, and the dispatch queue was idle after scoring. All five gates (build, check, correctness, sandbox, timeout) passed; failure was null. BEST and LATEST below are the board's records at this snapshot. These board run IDs are distinct from GitHub Actions IDs.

- **BEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.
- **LATEST:** `run-facbd5258123`; commit `40847ba5fde8714895533f7b47ce8fee48baa09e`; T=1.101349 s, M=527,192,064 bytes, S=721, D=1, K=6.978287, points=42.187440.


## Official board results — raw-feed snapshot 2026-10-30 23:10:48 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. The watcher was healthy at `01d4852e1271d5bec3d6de9aaa7641f8616730cb` with an idle queue. Both records passed build, check, correctness, sandbox, and timeout gates; failure was null. These are live-board measurements; BEST and LATEST are separately reported, and run IDs are not GitHub Actions IDs.

- **BEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.
- **LATEST:** `run-73912a09d633`; commit `01d4852e1271d5bec3d6de9aaa7641f8616730cb`; T=1.179690 s, M=527,945,728 bytes, S=721, D=1, K=6.740673, points=41.435163.


## Official board results — raw-feed snapshot 2026-10-31 00:12:03 UTC

HighVelocity (`highvelocity-7f330e`) remained registered. Watcher was healthy at `157f1d478136fd0d7950aa2a82e121c087ec7ec7`, with no queued or in-flight run. Every gate passed; failure was null. These are board measurements, and BEST/LATEST are tracked separately. Board run IDs are not GitHub Actions IDs.

- **BEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.
- **LATEST:** `run-53c1a976172c`; commit `157f1d478136fd0d7950aa2a82e121c087ec7ec7`; T=1.105358 s, M=528,588,800 bytes, S=721, D=1, K=6.961935, points=42.136499.


## Frontier bitmap engine integrated for official scoring — October 31, 2026

- Imported production source blob `ccb92c57f2e077fe25c2d372bbffda296a948fe0` from Track B PR #1 head `b7d7c907226eba27114e8a3c31640bdb76018514`; it is byte-identical to the source in qualified commit `5641b8fe7fa77cffcc8e06553ed0a49699df0141`. The prior official champion remains in parent commit `157f1d4` for rollback. Kept the official `HighVelocity` manifest and pinned Dockerfile; the developer manifest has a placeholder team value and was not imported.
- Qualification [CI 41147462315](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41147462315) passed full seeds 1–3, published seed-1 full/sample hashes, independent Python references for seeds 2–3, tiny/sample tests, differential/adversarial phrase and collision fixtures, ASan/UBSan, and restricted offline Docker. The production Docker uses the official pinned x86-64-v3 toolchain; native TSan passed the parallel adversarial fixture.
- Three paired production runs per seed measured candidate T=0.751904/0.739860/0.708414 s, peak M=55,582,720/55,066,624/55,238,656 bytes, S=607, D=1. Candidate K was 2.12–2.22× same-runner official-source K; scaling that ratio from board BEST K=6.988455 gives estimated K≈15.29 (range≈14.80–15.50), not an official result. The integrated commit set BEST at `run-0b8b1455c8cf`, K=13.772524; see the latest raw-feed receipt below.


## Official board results — raw-feed snapshot 2026-10-31 00:17:27 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`, queue idle. All five gates passed and failure was null. BEST and LATEST are reported separately; these are live-board IDs, not GitHub Actions IDs.

- **BEST:** `run-576d2d26d6c8`; commit `3059e71b54cd02e920e995d186a369b4be9c0aeb`; T=1.096353 s, M=529,350,656 bytes, S=721, D=1, K=6.988455, points=42.219058.
- **LATEST:** `run-147efa5f35b6`; commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.745195 s, M=56,193,024 bytes, S=607, D=1, K=13.622148, points=56.712280.


## Official board results — raw feed, 2026-10-31 00:23:55 UTC

HighVelocity (`highvelocity-7f330e`) was registered; watcher healthy at `73d8cecee9e50825a4f416b77c11fec448955782`; queue idle. All five gates passed for BEST and LATEST; failure was null.

- **BEST:** `run-147efa5f35b6`, commit `b8e654028f1fa9db3f4f50066d8eb60d559b9e67`; T=0.745195 s, M=56,193,024 bytes, S=607, D=1, K=13.622148, points=56.712280.
- **LATEST:** `run-51685e477229`, commit `73d8cecee9e50825a4f416b77c11fec448955782`; T=0.752069 s, M=55,832,576 bytes, S=607, D=1, K=13.577214, points=56.640533.


## Official board results — raw feed observed 2026-10-31 00:29:07 UTC

Watcher was healthy at `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca` (last checked 00:28:14 UTC); queue idle. All five gates passed; failure was null.

- **BEST = LATEST:** `run-0b8b1455c8cf`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677. New BEST.


## Official board results — raw feed observed 2026-10-31 00:34:36 UTC

Watcher healthy at `8233a6406105e8580d72bc059d91e48eb88e0868`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST:** `run-0b8b1455c8cf`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677.
- **LATEST:** `run-5e11d4027118`, commit `8233a6406105e8580d72bc059d91e48eb88e0868`; T=0.770530 s, M=55,504,896 bytes, S=607, D=1, K=13.429381, points=56.402800.


## Official board results — raw feed observed 2026-10-31 00:40:29 UTC

Watcher healthy at `b6f184e81a93554f4dd2b2e0284258345964f45f`, queue idle; all five gates passed for BEST and LATEST, failure null.

- **BEST:** `run-0b8b1455c8cf`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677.
- **LATEST:** `run-3245c8d1c9cf`, commit `b6f184e81a93554f4dd2b2e0284258345964f45f`; T=0.752699 s, M=55,681,024 bytes, S=607, D=1, K=13.578911, points=56.643246.


## Official board results — raw feed observed 2026-10-31 00:46:16 UTC

Watcher healthy at `94a98da3f2e1de31f3b6fc308194c698f3603249`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-0b8b1455c8cf`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677.
- **LATEST:** `run-d1b35c7ca81c`, commit `94a98da3f2e1de31f3b6fc308194c698f3603249`; T=0.738848 s, M=55,607,296 bytes, S=607, D=1, K=13.709232, points=56.850657.


## Official board results — raw feed observed 2026-10-31 00:51:41 UTC

Watcher healthy at `8b137acc1b2f3a83c9b7c422088b7b966357232e`, queue idle; all five gates passed for every latest run, failure null.

- **BEST:** `run-0b8b1455c8cf`, commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`; T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677.
- **LATEST:** `run-1cf33a7e21f4`, commit `8b137acc1b2f3a83c9b7c422088b7b966357232e`; T=0.754076 s, M=56,000,512 bytes, S=607, D=1, K=13.550992, points=56.598554.


## Frontier sparse-block candidate staged for official scoring — October 31, 2026

- Candidate source is byte-identical to `sd-tb` PR #2 qualified source at `a40228519bf2e202f993c1d6abe284ce5f9491c7`; latest PR head `4069aa907506fb5c0cc469421eeb74f93026e367` adds qualification notes only. Production blob `5de4b983d6be1434ead3f65451c0715742fffdfa`. Official manifest and pinned Dockerfile are retained unchanged; no runtime dependencies added.
- CI [41149282228](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41149282228) passed three full seeds with independent references and published hashes, tiny/sample, expanded collision/growth oracles, ASan/UBSan, TSan and restricted offline Docker. Candidate S=672, D=1 versus PR #1 S=607, D=1.
- Three paired full-scale seed medians on the same CI runner: T=0.679/0.649/0.652 s and M=56.36/59.48/59.07 MB, versus PR #1 K_local=12.793/13.123/13.002 and candidate K_local=14.049/14.214/14.202. The developer-runner full K formula improved 8.3–9.8%; the board result below is the measured official outcome for this exact source.
- Current official baseline: BEST `run-0b8b1455c8cf` on commit `0ae75f36afd0ddec3e9d07e8d9a5ea3300aeacca`, T=0.731083 s, M=55,795,712 bytes, S=607, D=1, K=13.772524, points=56.950677. LATEST `run-6f0b359c1dcc` on `a41c96b3bf47709cfa668b2243d84d827a1dddd8`, T=0.743594 s, M=55,676,928 bytes, S=607, D=1, K=13.661993, points=56.775702. Rollback to the official PR #1 source remains in parent `a41c96b`.

## Official board results — raw feed observed 2026-10-31 01:14:45 UTC

Watcher healthy at `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`, queue idle; all five gates passed, failure null.

- **BEST = LATEST:** `run-d6bcb1bfa301`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.575228 s, M=56,729,600 bytes, S=672, D=1, K=15.240808, points=59.150400. New BEST.


## Segmented-tape developer-main candidate (not submitted)

Developer `sd-tb/main` source blob `d968fb7e6f744c1b828141f201ed8de692f1f226` passed full-seed exactness, differential, sanitizer and pinned offline Docker qualification (CI run [41149380822](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41149380822)). Against its developer-branch baseline, measured full seed 1 T=0.86–0.92 s and RSS≈553 MiB vs 0.87–0.92 s and ≈622 MiB; seed 2 RSS≈549 MiB vs ≈619 MiB, with noisy near-flat T. This is not directly comparable to the official scoring box or the currently submitted sparse-block source; keep unpromoted pending a defensible equivalent-axis estimate and review of the newer frontier branch.


## Official latest board results — raw feed observed 2026-10-31 01:19:37 UTC

Watcher healthy at `266578e73fec11894c067b8b11a0910657a8ccff`, queue idle; all five gates passed for all four tracks, failure null.

- **BEST:** `run-d6bcb1bfa301`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.575228 s, M=56,729,600 bytes, S=672, D=1, K=15.240808, points=59.150400.
- **LATEST:** `run-e65ff6ba7ecb`, commit `266578e73fec11894c067b8b11a0910657a8ccff`; T=0.562097 s, M=60,981,248 bytes, S=672, D=1, K=15.196552, points=59.087253.


## Official board results — raw feed observed 2026-10-31 01:25:23 UTC

Watcher healthy at `09ee42d8656b9b599401140eb38d5d76b07a7566`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-d6bcb1bfa301`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.575228 s, M=56,729,600 bytes, S=672, D=1, K=15.240808, points=59.150400.
- **LATEST:** `run-245cb79aa5eb`, commit `09ee42d8656b9b599401140eb38d5d76b07a7566`; T=0.600840 s, M=55,017,472 bytes, S=672, D=1, K=15.004116, points=58.810520.


## Official board results — raw feed observed 2026-10-31 01:31:36 UTC

Watcher healthy at `ed14252dd1ed2a882887dffd6bb61950f03a1c85`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-d6bcb1bfa301`, commit `dddda29dafddf919e4cf3ebc66cb26ed5b5c872a`; T=0.575228 s, M=56,729,600 bytes, S=672, D=1, K=15.240808, points=59.150400.
- **LATEST:** `run-2a3df3131d0c`, commit `ed14252dd1ed2a882887dffd6bb61950f03a1c85`; T=0.581774 s, M=62,705,664 bytes, S=672, D=1, K=14.854275, points=58.592572.


## Official board results — raw feed observed 2026-10-31 01:36:50 UTC

Watcher healthy at `03742f51c5f91e7313584860fb6de63ad83fbae4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-f5d48fcf557e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.564032 s, M=57,286,656 bytes, S=672, D=1, K=15.361279, points=59.321369.
- **LATEST:** `run-f5d48fcf557e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.564032 s, M=57,286,656 bytes, S=672, D=1, K=15.361279, points=59.321369.


## Official board latest snapshot — raw feed observed 2026-10-31 01:42:00 UTC

Watcher healthy at `3077ed42f746f6ed84d122899e611b5af3dac0e4`, queue idle; all five gates passed for all tracks, failure null.

- **BEST:** `run-f5d48fcf557e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.564032 s, M=57,286,656 bytes, S=672, D=1, K=15.361279, points=59.321369.
- **LATEST:** `run-2648b371f76e`, commit `3077ed42f746f6ed84d122899e611b5af3dac0e4`; T=0.571133 s, M=56,717,312 bytes, S=672, D=1, K=15.296011, points=59.228910.

## Official board results — raw feed observed 2026-10-31 01:50:28 UTC

Watcher healthy at `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`, queue idle. All five gates passed for all four tracks; failures were null.

- **BEST:** `run-f5d48fcf557e`, commit `03742f51c5f91e7313584860fb6de63ad83fbae4`; T=0.564032 s, M=57,286,656 bytes, S=672, D=1, K=15.361279, points=59.321369.
- **LATEST:** `run-9d2d0a5dc3e6`, commit `d8e6e1c755acab6ab8ef167efed1b64d44f96c54`; T=0.574283 s, M=56,918,016 bytes, S=672, D=1, K=15.243231, points=59.153851.

## Official rollback snapshot — raw feed 2026-10-31 01:55 UTC

`run-6b648cd93457` scored commit `4567e5529f0418efdd26c132701f1bf296bcb49d`; all five gates passed, failure null. **LATEST:** T=0.569547 s, M=58,552,320 bytes, S=672, D=1, K=15.220059, points=59.120817. **BEST:** `run-f5d48fcf557e`, K=15.361279, points=59.321369.

## Official board snapshot — raw feed 2026-10-31 02:00:12 UTC

Watcher healthy at `6bf7383dc5439ccd0768435c1932c243e16c0584`, queue idle. All five gates passed, failure null. **BEST = LATEST:** `run-071238af51d9`, T=0.558953 s, M=56,795,136 bytes, S=672, D=1, K=15.457529, points=59.457004. New BEST on unchanged B source.


## Frontier streaming promotion candidate — official board promotion (2026-10-31)

- Imported the verified `sd-tb` main source blob `4b386e5587b690f2b12a9f2cd6d9d59cb178594d` (developer main HEAD `48887044d40a71753a28b5386f2b015ad4605371`). Its three-seed qualification [CI 41157659217](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41157659217) passed full seed-1 published SHA, full seed-2/3 independent Python references, differential/adversarial and CRC32C collision tests, sample/tiny hashes, and pinned offline Docker.
- Interleaved runner-local Docker medians were 0.579/0.573/0.575 s vs the preceding streaming candidate's 0.677/0.671/0.668 s; candidate peak memory was about 43 MiB, S=742, D=1. These are qualification measurements, not official board results.
- Parent official HEAD `062d7e54614520ed5991920db8bd63579998b663` had BEST `run-071238af51d9` (T=0.558953 s, M=56,795,136 bytes, S=672, D=1, K=15.457529) and LATEST `run-c34ebd32f0d9` (T=0.571388 s, M=59,637,760 bytes, S=672, D=1, K=15.139800). The official board result is recorded below; prior source remains in Git history for rollback.


### Official board promotion — 2026-10-31 02:34 UTC

- Raw feed run `run-de8c2b3fc7da` on commit `8d5bc54c93a054ba70e651a7d9b802fcf9140276` passed build, check, correctness, timeout and sandbox gates. BEST and LATEST are this run: T=0.488654 s, M=47,063,040 bytes, S=742, D=1, K=16.912119, points=61.409902.
- Compared with prior BEST `run-071238af51d9` (T=0.558953 s, M=56,795,136 bytes, S=672, K=15.457529), K improved 9.4%, T fell 12.6%, memory fell 17.1%, and S rose 10.4%. This qualifies the new B source for promotion; D remains unchanged and the prior B source is retained in Git history.


## Official board results — raw feed observed 2026-10-31 03:05:10 UTC

The watcher was healthy at commit `b453c295cdbca2e3c740d71d6c35e57b8dec3662`. Run `run-e7ef1e703252` on this commit passed build, check, correctness, timeout and sandbox gates. LATEST: T=0.489432 s, M=50,085,888 bytes, S=742, D=1, K=16.689584, points=61.122275. BEST remains `run-de8c2b3fc7da`: T=0.488654 s, M=47,063,040 bytes, S=742, D=1, K=16.912119, points=61.409902. This run did not replace BEST; retain the current source and track rollback history.


## Board baseline before multi-track trial — raw S3 feed 2026-10-31 03:49:18 UTC

- **BEST:** `run-de8c2b3fc7da`, commit `8d5bc54c93a054ba70e651a7d9b802fcf9140276`; T=0.488654 s, M=47,063,040 B, S=742, D=1, K=16.912119, points=61.409902.
- **LATEST:** `run-4fbd4821490a`, official HEAD `a30276e460e00aa279aa41cca913a10a90a1a6a8`; T=0.508939 s, M=47,771,648 B, S=742, D=1, K=16.522199, points=60.903392. All five gates passed. B PRs #5/#6 were reviewed but not included: their reported seed-1 local K (15.218973 / 14.881114) is below the official BEST and remains a scoring-box experiment only.

## Unchanged B source rescored — run `run-ed9009e37ba4`

- Scored on commit `f91d9c075066881eb480cd7d27a9f33bfdc43350`; all five gates passed. T=0.484438 s, M=47,280,128 B, S=742, D=1, K=16.969925, points=61.483996. This set a new BEST on the existing B source, up from `run-de8c2b3fc7da` K=16.912119; no B code was changed.


## Official baseline before six-worker hybrid trial — raw feed 2026-10-31 04:14 UTC

On official HEAD `ec1140f4d0bd607a02b9fae4be61ce5fe3bae986`, LATEST `run-061719b36232` passed all five gates: T=0.480930 s, M=49,573,888 B, S=742, D=1, K=16.871093, points=61.357161. BEST remains `run-ed9009e37ba4` on `f91d9c0`: T=0.484438 s, M=47,280,128 B, S=742, D=1, K=16.969925, points=61.483996.

## Controlled six-worker hybrid trial — promoted

- Imported Track B source blob `e97e6f5e0045d64771180d59c57b3115cc742abb` from PR #7 head `ca9fb5fabeeed55830243f533d965667c4e72275`. Its exact source blob was present in qualification commit `7dad9d2`; CI run [41165413401](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41165413401) passed three full-seed references/hashes, expanded differential/adversarial tests, ASan/UBSan, TSan, and pinned offline Docker. Candidate Dockerfile and manifest match the official files; D=1.
- Developer five-run trimmed full-seed measurements: T=0.334020/0.331050/0.335371 s; M=37,122,048/37,105,664/37,085,184 B; S=857; K_local=20.289576/20.380386/20.248668. These are runner results, not official scores; reported K gain is about 4% over the same-run official source.
- Prior official source blob `4b386e5587b690f2b12a9f2cd6d9d59cb178594d` is preserved in parent commit `ec1140f` for rollback. Merge PR #7 only if the official run passes all gates and beats BEST.


- Official run `run-8558a8ee640d` on `a2f99921eaf302381af4fa63e6b131588c3fb572` passed build, check, correctness, timeout and sandbox gates. **BEST = LATEST:** T=0.393819 s, M=45,469,696 B, S=857, D=1, K=18.563313, points=63.432774.
- Versus prior BEST `run-ed9009e37ba4` (T=0.484438 s, M=47,280,128 B, S=742, D=1, K=16.969925, points=61.483996), K improved 9.39%, T fell 18.71%, M fell 3.83%, while S rose 15.50%. This promotes the six-worker hybrid; rollback source remains in parent `ec1140f`.
- Developer PR #7 was merged to `sd-tb/main` as `f28305ada8f78b4278a461e35b08d175be038d07`; main source blob matches the tested official source blob `e97e6f5e0045d64771180d59c57b3115cc742abb`.


## Official board snapshot — 2026-10-31 04:21:29 UTC

HighVelocity (`highvelocity-7f330e`) watcher was healthy at official HEAD `a62ff8d662a8f342256a53b20e05a3e2a9af6231`; queue clear. All five gates passed.

- **BEST = LATEST:** `run-fcc63900551a`; T=0.300767 s, M=44,257,280 B, S=857, D=1, K=21.356800, points=66.476809. This replaces `run-8558a8ee640d` (T=0.393819 s, M=45,469,696 B, K=18.563313); K rose 15.05%, T fell 23.63%, and memory fell 2.66% on the new measurement.


## Official board snapshot — 2026-10-31 04:25:59 UTC

- **BEST = LATEST:** `run-5bb26ac0d0c9` on `6ce631e9aed748609f3fbd289ec599cb4abf152d`; all five gates passed. T=0.298829 s, M=44,855,296 B, S=857, D=1, K=21.368503, points=66.488705. K edged up 0.05% from previous BEST `run-fcc63900551a` (21.356800); no B source change was made in this trial.


## Official board snapshot — 2026-10-31 04:30:35 UTC

- **BEST:** `run-5bb26ac0d0c9`; T=0.298829 s, M=44,855,296 B, S=857, D=1, K=21.368503, points=66.488705.
- **LATEST:** `run-8034f1a8988b` on `952084e36d4a8309c21c175f7208a40fe40c2702`; T=0.299654 s, M=45,486,080 B, S=857, D=1, K=21.279552, points=66.398124. All five gates passed.


## Official board snapshot — 2026-10-31 06:18:39 UTC

- **BEST:** `run-5bb26ac0d0c9`; T=0.298829 s, M=44,855,296 B, S=857, D=1, K=21.368503, points=66.488705.
- **LATEST:** `run-3cecc714d492` on `bd1e696b8a738a9f6d52c2faa16d9a6244c64d5e`; all five gates passed. T=0.315781 s, M=44,617,728 B, S=857, D=1, K=20.809121, points=65.912687.


## Official board snapshot — 2026-10-31 06:23:31 UTC

- **BEST:** `run-5bb26ac0d0c9`; T=0.298829 s, M=44,855,296 B, S=857, D=1, K=21.368503, points=66.488705.
- **LATEST:** `run-625071922c5a` on `8e70985f8a07fc6b5adaa9435c4d6b83638a2665`; all five gates passed. T=0.306599 s, M=45,068,288 B, S=857, D=1, K=21.076022, points=66.189432.

## 64-byte AVX2 scanner official trial — October 31, 2026

- Imported the promoted `sd-tb/main` source from HEAD `4e4b0cc6eecf3a4fe2d18c05217f264e72e1f049`, source blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9`. The exact blob passed developer Actions qualification [41172484797](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41172484797): pinned production Docker builds; differential and adversarial tests; independent full seeds 1–3, sample and tiny inputs; ASan/UBSan and TSan. The workflow's per-seed coefficient assertions require candidate K_local to beat both development and previous variants. The artifact's numeric axes were not available to this integrator, so no developer timing values are claimed here.
- Local native build and differential plus frontier-adversarial suites passed, including all byte classes/SIMD alignments, collision, dictionary-growth and worker/block-boundary cases. This is an additional local check; the pinned CI run is the container/build evidence.
- Before trial, official **BEST** was `run-5bb26ac0d0c9` (T=0.298829 s, M=44,855,296 B, S=857, D=1, K=21.368503); **LATEST** was `run-3e1218c0aef8` (T=0.316117 s, M=44,797,952 B, S=857, D=1, K=20.781298) on `0be320bade0ac6b5bc47cdb573b3a3811252de18`. Both passed all gates. The prior official source is retained in the parent commit for rollback; the candidate's board score is pending.

- Official board run `run-2b8dc2af774e` scored commit `f3bd76617870c71c81594817b54ad366113718bc`; all five gates passed. T=0.299632 s, M=44,331,008 B, S=860, D=1, K=21.378880, points=66.499248. **BEST = LATEST:** K improves 0.049% over `run-5bb26ac0d0c9` (K=21.368503), with T 0.27% higher, M 1.17% lower, and S three lines higher. Promote this exact Track B source; earlier source remains in the parent commit.

## Official board snapshot — 2026-10-31 07:06:34 UTC

- `run-7be0ced31374` scored `281c60f59cbe6c6a8c51f77aba7daad102151abd`; all five gates passed. LATEST: T=0.304786 s, M=44,695,552 B, S=860, D=1, K=21.162658. BEST remains `run-2b8dc2af774e` (K=21.378880); the scanner source is retained because its earlier official trial set the current BEST.

## Official board snapshot — 2026-10-31 07:12:34 UTC

- `run-04a7116196c9` scored `aa84dc52fefa309db4dbc5c2b9aefc07863ea13a`; all five gates passed. LATEST and new BEST: T=0.300165 s, M=42,844,160 B, S=860, D=1, K=21.392007, points=66.512577. K is 0.061% above the previous BEST `run-2b8dc2af774e` (21.378880); the same B source remains promoted.

## Official board snapshot — 2026-10-31 07:17:07 UTC

- `run-e4d246e15ac5` scored exact HEAD `15cc7c6f38a26d0f3515727d6d217ba4d95094b9`; all five gates passed. LATEST: T=0.302998 s, M=45,654,016 B, S=860, D=1, K=21.135129, points=66.250245. BEST remains `run-04a7116196c9` (K=21.392007).


## Official board snapshot — 2026-10-31 12:11:52 UTC

- **BEST:** `run-04a7116196c9`, T=0.300165 s, M=42,844,160 B, S=860, D=1, K=21.392007, points=66.512577.
- **LATEST:** `run-3cb698d73c4f` on `2b5afc9408dcd202ca3f113e100d02fc673d04ee`; all five gates passed. T=0.311329 s, M=43,327,488 B, S=860, D=1, K=21.004956, points=66.116088.
- Candidate source blob `b49b7ed50b672c072709e93272a77e2a18f7e169` is from `sd-tb/main` HEAD `c6ed9465a5f49db6473461369097e5d49ae46b9f`; exact-source qualification CI `41196378364` passed. CI’s paired three-seed comparison found 1024-document blocks faster and lower-memory than 2048 blocks, while maintaining exact output. Candidate board result is pending; parent commit retains the known-good source for rollback.


## Official candidate result — 2026-10-31 12:15:45 UTC

- Board run `run-b198debee5e1` scored `187269afc6efbeee7ac01b4f623f7c7f049ea44b`; all five gates passed. Candidate LATEST: T=0.433684 s, M=29,081,600 B, S=874, D=1, K=17.753865, points=62.464646. BEST remains `run-04a7116196c9`, K=21.392007. Despite 32.1% lower memory, K fell 17.01% versus BEST, with slower T and 14 more source lines. Reject the 1024-block candidate and restore known-good source blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9` from parent commit `2b5afc9`; the rejected `b49b7ed50b672c072709e93272a77e2a18f7e169` candidate remains recoverable in commit `187269a`.


## Official latest — 2026-10-31 12:21:24 UTC

- **BEST:** `run-04a7116196c9`, T=0.300165 s, M=42,844,160 B, S=860, D=1, K=21.392007. **LATEST:** `run-7449c0cc2695` on `ca8f1811fcefc6fdb6cc5678754f7387791f5f31`, T=0.300804 s, M=45,936,640 B, S=860, D=1, K=21.185901; all five gates passed. This is the known-good scanner source after the rejected block-size trial; the 0.96% K difference is ordinary single-run variation.


## Official latest — 2026-10-31 12:26:53 UTC

- BEST remains `run-04a7116196c9`, K=21.392007. LATEST `run-091a137baa46` on `f3b24e34ddb937f3bca3317cfd5d79bf021509fa` passed all gates: T=0.303596 s, M=44,658,688 B, S=860, D=1, K=21.207592, points=66.324568. The source is the known-good 64-byte scanner blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9`; the 0.86% K gap is normal board-run variation.


## Official latest — 2026-10-31 12:33:30 UTC

- BEST remains `run-04a7116196c9`, K=21.392007. LATEST `run-373ca7e45b89` on `f477933130ce23aa311f60d3486480ab5de6fff8` passed all gates: T=0.306341 s, M=43,458,560 B, S=860, D=1, K=21.175272. The source is unchanged known-good scanner blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9`; the 1.01% gap is run variation.


## Official latest — 2026-10-31 12:40:40 UTC

- **BEST:** `run-04a7116196c9`, K=21.392007. **LATEST:** `run-af64e50dbbf1` on `0923ede528139a79896a6bfe1bb67934f74c5951`, all five gates passed: T=0.323075 s, M=44,916,736 B, S=860, D=1, K=20.534648, points=65.624363. Same promoted scanner source blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9`; 4.01% below BEST.

## Official same-source rerun — 2026-10-31 13:17 UTC

- Run `run-511275801433` on `b0e30144ba58e2c3b3c86c8b1fd26dffa1e655b5` passed all five gates: T=0.332854 s, M=44,736,512 B, S=860, D=1, K=20.247027. BEST remains `run-04a7116196c9` (K=21.392007). Source blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9` is unchanged; this repeat does not change promotion.

## PR #8 12-worker hybrid — promoted after official board trial, 2026-10-31

- Exact source blob `76946cc77205b4f115aa32bed459e0980c8d143c` from `frontier/b-sol-hybrid12` (qualified source commit `ea351a5c9a3eb985faab60326e61387b6366b8b6`; current PR head `879fcf8690aa9ae582e33938e1ee0f22d4dc4108` changes documentation only). Qualification run `41165413401` passed three full references, published sample/full hashes, expanded differential and boundary tests, ASan/UBSan, TSan, and pinned production-Docker oracles.
- Full seeds 1/2/3 on a four-logical-CPU runner: five-run trimmed T=0.324628/0.325807/0.326278 s, M=42,610,688/41,828,352/42,856,448 B, S=925, D=1, K_local=20.346611/20.309763/20.295099. This candidate uses 12 workers and is intended for the scoring host's 12 logical threads; these runner K values are not official scores. Official run `run-02a47f69ba31` on `f1bcd2033e061028929c445c964768331d1a6f5e` passed all five gates: T=0.242534 s, M=51,937,280 B, S=925, D=1, K=22.771515, points=67.869597. This is the new BEST, +6.45% K over `run-04a7116196c9` (21.392007). PR #8 was merged to `sd-tb/main` at `d7845bc6ac6a77547121daf1fda751e34999b325`; source blob remains `76946cc77205b4f115aa32bed459e0980c8d143c`. Parent commit retains old B source blob `30dcb9f6a6472f390a9513f5739fd040bd1bd3c9` for rollback.


## Official same-source repeat — 2026-10-31 14:17 UTC

- **BEST and LATEST:** `run-a4f446831333` on `af33cf8053e100e92405aabcfa50d0278203daa1`, all five gates passed: T=0.242208 s, M=49,475,584 B, S=925, D=1, K=23.009207, points=68.095083. This repeats the promoted B source blob `76946cc77205b4f115aa32bed459e0980c8d143c` and improves the first official result `run-02a47f69ba31` by 1.04% K; no source change.


## Official same-source repeat — 2026-10-31 14:22 UTC

- **BEST and LATEST:** `run-5accd9f1743a` on `e5e94a469faec38eaaf180210e468ac3060b3023` passed all five gates: T=0.238879 s, M=50,163,712 B, S=925, D=1, K=23.105063, points=68.185358. This repeats promoted source blob `76946cc77205b4f115aa32bed459e0980c8d143c` and improves prior BEST `run-a4f446831333` by 0.42%; no source change.

## Official latest — 2026-10-31 15:12 UTC

- LATEST `run-11de9ca0c6e3` on `1657706f033d676bb97f0df87e3386978b694387` passed all five gates: T=0.238881 s, M=50,245,632 B, S=925, D=1, K=23.097428, points=68.178181. BEST remains `run-5accd9f1743a`, K=23.105063. Promoted B source blob `76946cc77205b4f115aa32bed459e0980c8d143c` was unchanged.

## Official latest — 2026-10-31 15:21 UTC

- LATEST `run-9a2ea67093b5` on `480a8e3def26af26e10298d6b043bf2195c82ec3` passed all five gates: T=0.240934 s, M=54,124,544 B, S=925, D=1, K=22.659284, points=67.762309. BEST remains `run-5accd9f1743a`, K=23.105063. Promoted source blob `76946cc77205b4f115aa32bed459e0980c8d143c` was unchanged; this is a lower same-source repeat.

## Official latest — 2026-10-31 16:13 UTC

- LATEST `run-0781dd79dacb` on `8298e2cbe0d21ffd4688bb23b625f988fdd4128d` passed all five gates: T=0.244675 s, M=49,881,088 B, S=925, D=1, K=22.855572, points=67.949605. BEST remains `run-5accd9f1743a`, K=23.105063. B source blob `76946cc77205b4f115aa32bed459e0980c8d143c` was unchanged.


## Official latest — 2026-10-31 16:19 UTC

- LATEST `run-2285de3f856c` on submission `d4b9c4d51f4d0c3fc2d58a1fc9bf6c66ef642ed9` passed all five board gates: T=0.240157 s, M=50,163,712 B, S=925, D=1, K=23.043504, points=68.127426. BEST remains `run-5accd9f1743a`, K=23.105063; promoted B source blob `76946cc77205b4f115aa32bed459e0980c8d143c` unchanged.


## Official latest — 2026-10-31 16:27 UTC

- LATEST `run-0975db393f37` on `70d512481b36d111e017909f4b76e257f69db9ea` passed all five board gates: T=0.243952 s, M=50,008,064 B, S=925, D=1, K=22.877780, points=67.970694. BEST remains `run-5accd9f1743a`, K=23.105063; source blob `76946cc77205b4f115aa32bed459e0980c8d143c` unchanged.

## Official latest — 2026-10-31 16:33 UTC

- LATEST `run-df74e256f12e` on official commit `0ef3758e08e015c6f1ba97b9d36966ec151efc40` passed all five board gates: T=0.244353 s, M=49,971,200 B, S=925, D=1, K=22.862372, points=67.956065. BEST remains `run-5accd9f1743a`, K=23.105063; promoted source blob `76946cc77205b4f115aa32bed459e0980c8d143c` unchanged.


## Full-team board results — 2026-10-31 16:39–16:45 UTC

All five gates passed. The promoted B source blob `76946cc77205b4f115aa32bed459e0980c8d143c` was unchanged across these runs.

- **BEST / LATEST:** `run-c050e7922fc2` on official commit `242c9bf8b5169359fbe30b30245cf799f1662304`: T=0.237908 s, M=49,979,392 B, S=925, D=1, K=23.169218, points=68.245568. This is the current BEST.
- Previous receipts: `run-a34171117109` on `92c095f030bd9519de41ab7201a944cc9d94cbd6`: T=0.242076 s, M=50,561,024 B, S=925, K=22.915801; `run-df74e256f12e` on `0ef3758e08e015c6f1ba97b9d36966ec151efc40`: K=22.862372.
- The latest K is 0.23% above the previous BEST `run-5accd9f1743a` (K=23.105063). Source did not change; this is a new board measurement, not a claimed source optimization.


## Full-team baseline before six-worker trial — 2026-10-31 16:49 UTC

All five gates passed on official commit `6a01ff11b17d179835197e73cbab6518a6651b79` with the previous 12-worker source blob `76946cc77205b4f115aa32bed459e0980c8d143c`.

- **LATEST:** `run-199d4e836760`: T=0.241910 s, M=50,896,896 B, S=925, D=1, K=22.893327, points=67.985446.
- Previous best remains `run-c050e7922fc2`, K=23.169218; the new result is lower by 1.19% with no source change.

## PR #5 six-worker candidate — official trial staged

Candidate `sd-tb` head `cba79e06d7149da14fa1b5d36f4be079526f1cdc`, source blob `510c2a13dccb26c712ff2239000817dd5b4a900a`, uses six workers and 1,536-document blocks. It is staged solely for a controlled scoring-box comparison; the previous official 12-worker source remains in commit `6a01ff11b17d179835197e73cbab6518a6651b79` for rollback.

- Developer GitHub Actions run [41159913998](https://github.com/insightlabs38-pixel/sd-tb/actions/runs/41159913998) succeeded: three full references, sample/tiny, differential and adversarial cases, pinned offline Docker, ASan/UBSan, TSan, published hashes, and 4/6/8/12-worker boundaries.
- Four-logical-CPU local full-seed T values were 0.610445/0.620926/0.606104 s, M=41,570,304–41,934,848 B, S=781, D=1. Those oversubscribed runner results do not establish scoring-box performance. Official T/M/S/D/K are pending.


## PR #5 six-worker official trial — rejected on performance

All five gates passed for candidate source blob `510c2a13dccb26c712ff2239000817dd5b4a900a` on official commit `77a70106fecd5098a0a152a47f8e7383a3c1e9c5`. Run `run-3afd6a73fb21` measured T=0.426064 s, M=48,852,992 B, S=781, D=1, K=17.839474, points=62.569102.

- Compared with the immediately preceding 12-worker result `run-199d4e836760` (T=0.241910 s, M=50,896,896 B, S=925, K=22.893327), the six-worker trial reduced M by 4.0% and S by 144, but T rose by 76.1% and K fell by 22.1%. It is well below BEST `run-c050e7922fc2`, K=23.169218.
- Reject PR #5 for promotion and restore the 12-worker source blob `76946cc77205b4f115aa32bed459e0980c8d143c`; the candidate remains in official parent history and its developer PR stays open. Correctness passed; scoring efficiency did not.


## PR #5 six-worker official trial — rejected on performance

All five gates passed for candidate source blob `510c2a13dccb26c712ff2239000817dd5b4a900a` on official commit `77a70106fecd5098a0a152a47f8e7383a3c1e9c5`. Run `run-3afd6a73fb21` measured T=0.426064 s, M=48,852,992 B, S=781, D=1, K=17.839474, points=62.569102.

- Compared with the immediately preceding 12-worker result `run-199d4e836760` (T=0.241910 s, M=50,896,896 B, S=925, K=22.893327), the six-worker trial reduced M by 4.0% and S by 144, but T rose by 76.1% and K fell by 22.1%. It is well below BEST `run-c050e7922fc2`, K=23.169218.
- Reject PR #5 for promotion and restore the 12-worker source blob `76946cc77205b4f115aa32bed459e0980c8d143c`; the candidate remains in official parent history and its developer PR stays open. Correctness passed; scoring efficiency did not.


## Rollback verified — 2026-10-31 17:00 UTC

After rejecting PR #5, official commit `74a4fb7456ce5fb8b10ef5b0eeef2d58289fdc59` restored source blob `76946cc77205b4f115aa32bed459e0980c8d143c`. All five gates passed. **LATEST:** `run-fae9d65ec17a`, T=0.249936 s, M=51,023,872 B, S=925, D=1, K=22.511529, points=67.620250. The promoted hybrid12 source remains BEST at `run-c050e7922fc2`, K=23.169218. This confirms the executable rollback; the low six-worker result remains documented above.


## Full-team board run after B rollback — 2026-10-31 17:05 UTC

All five gates passed on commit `23be16823a7232064b3090b805ff80b6c086cfa9` with restored source blob `76946cc77205b4f115aa32bed459e0980c8d143c`. **LATEST:** `run-770689ed285d`, T=0.243058 s, M=50,266,112 B, S=925, D=1, K=22.896235, points=67.988203. BEST remains `run-c050e7922fc2`, K=23.169218. The rejected PR #5 result and verified rollback are recorded above.


## Full-team board result — 2026-10-31 17:10 UTC

All five gates passed on official commit `a2ead921538e31adbc9a9d0ecafc6b2e16f9e818` with restored hybrid12 source blob `76946cc77205b4f115aa32bed459e0980c8d143c`. **LATEST:** `run-bb7aeaf0757b`, T=0.244655 s, M=49,897,472 B, S=925, D=1, K=22.855005, points=67.949066. BEST remains `run-c050e7922fc2`, K=23.169218.


## Full-team board result — 2026-10-31 17:19 UTC

All five gates passed on official commit `c4cb49fedd910dd65dc0719c113b06fa2e9c2476` with the unchanged restored hybrid12 source. **LATEST:** `run-30f1d62c541c`, T=0.258027 s, M=49,549,312 B, S=925, D=1, K=22.286095, points=67.401699. BEST remains `run-c050e7922fc2`, K=23.169218.


## Full-team board result — 2026-10-31 17:30 UTC

All five gates passed on rollback HEAD `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122` with the unchanged hybrid12 source. **LATEST:** `run-bb9bb994b149`, T=0.240934 s, M=49,946,624 B, S=925, D=1, K=23.026282, points=68.111191. BEST remains `run-c050e7922fc2`, K=23.169218.


## Official board results — 2026-10-31 18:17 UTC

On official commit `a91a77e9ad3a54d93385b3bfc5231da589395f1c`, unchanged Track B source passed all five gates.
- **BEST/LATEST:** `run-dcebadac870d`; T=0.236395 s, M=49,901,568 B, S=925, D=1, K=23.250490, points=68.321605.
- This replaces the prior BEST `run-c050e7922fc2`, K=23.169218. Track B source was unchanged; this receipt reflects a new full-team scoring run.


## Official results — run-b90943d61160 (2026-10-31 18:25 UTC)

All five gates passed on commit `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21`; source is unchanged. **LATEST:** `run-b90943d61160`, T=0.239293 s, M=50,118,656 B, S=925, D=1, K=23.089217, points=68.170460. **BEST** remains `run-dcebadac870d`, K=23.250490.


## Official latest — run-7ed447399d49 (2026-10-31 18:31 UTC)

All five gates passed on unchanged B source. **LATEST:** T=0.244164 s, M=50,876,416 B, S=925, D=1, K=22.789247, points=67.886498. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-f20ccb7c4eb9 (2026-10-31 18:37 UTC)

All five gates passed. **LATEST:** T=0.238619 s, M=51,707,904 B, S=925, D=1, K=22.977892, points=68.065509. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-f03691be329d (2026-10-31 18:44 UTC)

All five gates passed. **LATEST:** T=0.240225 s, M=50,765,824 B, S=925, D=1, K=22.985327, points=68.072535. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-3cdfb58ecbd8 (2026-10-31 18:50 UTC)

All five gates passed. **LATEST:** T=0.237953 s, M=50,675,712 B, S=925, D=1, K=23.103008, points=68.183426. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-82611a8d58f7 (2026-10-31 18:56 UTC)

All five gates passed. **LATEST:** T=0.237917 s, M=50,180,096 B, S=925, D=1, K=23.150216, points=68.227752. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-10cca0434191 (2026-10-31 19:02 UTC)

All five gates passed. **LATEST:** T=0.238907 s, M=50,040,832 B, S=925, D=1, K=23.115045, points=68.194737. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-588f33aa5a50 (2026-10-31 19:08 UTC)

All five gates passed. **LATEST:** T=0.241121 s, M=49,053,696 B, S=925, D=1, K=23.100545, points=68.181111. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-ad17d228659f (2026-10-31 19:15 UTC)

All five gates passed. **LATEST:** T=0.267419 s, M=50,163,712 B, S=925, D=1, K=21.837354, points=66.960001. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-367b1e01bf34 (2026-10-31 19:24 UTC)

All five gates passed. **LATEST:** T=0.255559 s, M=51,478,528 B, S=925, D=1, K=22.223030, points=67.340164. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-28661389c667 (2026-10-31 19:29 UTC)

All five gates passed. **LATEST:** T=0.238160 s, M=52,445,184 B, S=925, D=1, K=22.934990, points=68.024928. **BEST** remains `run-dcebadac870d` (K=23.250490).


## Official latest — run-3ff992c373fc (2026-10-31 19:42 UTC)

All five gates passed. **LATEST:** T=0.245942 s, M=49,774,592 B, S=925, D=1, K=22.806371, points=67.902810. **BEST** remains `run-dcebadac870d` (K=23.250490).

## Official board run — 2026-10-31 19:46 UTC

Run `run-3ff992c373fc` scored commit `2602c63339f532be813056b0c05bb573835f6766`; all five gates passed, failure null. **LATEST:** T=0.245942 s, M=49,774,592 bytes, S=925, D=1, K=22.806371. **BEST** remains `run-dcebadac870d`, K=23.250490.

## Official board result — commit 3384246, dispatch 2026-10-31 19:52 UTC

Run `run-e69497fa31df`; all five gates passed. T=0.233890 s, M=51,953,664 bytes, S=925, D=1, K=23.187025, points=68.262251. **BEST:** `run-dcebadac870d`, K=23.250490. **LATEST:** `run-e69497fa31df`.

## Official board result — commit 13b8fec, dispatch 2026-10-31 19:57 UTC

Run `run-83ba2924142d`; all five gates passed. T=0.237968 s, M=50,094,080 bytes, S=925, D=1, K=23.155679, points=68.232876. **BEST:** `run-dcebadac870d`, K=23.250490. **LATEST:** `run-83ba2924142d`. Next official frontier trial is B PR #5 (6 workers), exact head `cba79e06d7149da14fa1b5d36f4be079526f1cdc`, source blob `510c2a13dccb26c712ff2239000817dd5b4a900a`; qualification logs exercise the exact 6/12-worker source revisions, full references, sanitizers, and offline Docker. Local runner results are not official scaling evidence.

## Official board result — commit 555cd61, dispatch 2026-10-31 20:03 UTC

Run `run-0ae89c59b073`; all five gates passed. T=0.358443 s, M=50,008,064 bytes, S=781, D=1, K=19.358853, points=64.343981. **BEST:** `run-dcebadac870d`, K=23.250490. **LATEST:** `run-0ae89c59b073`; B PR #5 is rejected on complete K, retaining the earlier champion source. PR #6's exact source had weaker local K and higher peak memory than PR #5, so no board trial is planned.


## Official board result — trial commit 9743d05 (2026-10-31 20:09:57 UTC)

Run `run-ca66bb3d645f`; all five gates passed. T=0.260087 s, M=51,748,864 B, S=925, D=1, K=22.005670, points=67.126730. **BEST** remains `run-dcebadac870d` at K=23.250490; **LATEST** is this champion-source repeat.


## Official board result — commit 3c9845a (2026-10-31 20:15:02 UTC)

Run `run-48eb79091057`; all five gates passed. T=0.249572 s, M=51,339,264 B, S=925, D=1, K=22.500192, points=67.609311. **LATEST** is this restored champion-source run; **BEST** remains `run-dcebadac870d` at K=23.250490.
