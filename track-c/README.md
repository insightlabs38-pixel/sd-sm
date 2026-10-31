# Track C: Join

Dependency-free C++17 CSV parser and exact aggregator for Track C. It handles quoted fields and escaped quotes, uses exact name comparisons with a synchronized overflow path, and maps unknown record region IDs through the frozen input range (up to 9,999,999) to `_UNMATCHED`.

The known-good official source is retained in parent `f0e8236ee3641950287d6e2dd25814fb4b6ef9bb` (blob `7def6ac05e18fcf871310f37abade9ca1a904760`), with BEST `run-8f98e6ec4091`, K=20.413289. A current-main SSE2 quote-scanning candidate (source blob `4ca129b0ca9596554d052aadb9d5e751496cc754`) is staged for official trial; its exact source passed developer CI [41229750254], but board scoring is pending.
