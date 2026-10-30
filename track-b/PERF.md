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


## Official board receipts — feed snapshot 2026-10-30 22:40 UTC

HighVelocity (`highvelocity-7f330e`) is registered. At this snapshot the board watch was healthy at submission HEAD `3e6b84d7e642181423fbec9e571644f11e7e430f`, with no queued or in-flight team run. The receipts below are actual live-board records; all five gates (build, check, correctness, sandbox, timeout) passed. Earlier “no board run/registration” notes are historical and superseded by this section. GitHub Actions IDs elsewhere are CI, not board runs.

- **BEST:** `run-b247a4fdb6e7`; commit `3e6b84d7e642181423fbec9e571644f11e7e430f`; T=1.119754 s, M=528,723,968 bytes, S=721, D=1, K=6.916684, points=41.994897.
- **LATEST:** `run-b247a4fdb6e7`; commit `3e6b84d7e642181423fbec9e571644f11e7e430f`; T=1.119754 s, M=528,723,968 bytes, S=721, D=1, K=6.916684, points=41.994897.
