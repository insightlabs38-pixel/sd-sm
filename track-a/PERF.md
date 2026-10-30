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
