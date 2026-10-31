# Track C: Join

A byte-oriented C++17 parser handles hostile quoted CSV and maps lookup regions through a dense table. Six workers share an exact-name table with 131,072 control-byte-probed slots and inline short keys; a synchronized overflow path preserves exact equality at higher cardinality. Record IDs beyond the lookup range map to `_UNMATCHED`, including valid values through 9,999,999.

No third-party runtime dependencies. This source from merged `sd-tc` PR #5 (`0c026e2b3d0003f85f3ce88de1fc94522128d0b6`) is the current board-qualified C candidate. Run `run-dd8b39dbecd2` passed all five gates with T=0.085478 s, M=12,455,936 B, S=537, and K=20.109251. It improved K by 0.25% and reduced measured memory by 39.6% versus the immediately preceding C BEST. The prior inline-name source remains in official Git history for rollback.
