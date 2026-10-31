# Track C: Join

A byte-oriented C++17 parser handles hostile quoted CSV and maps lookup regions through a dense table. Six workers share an exact-name table with 131,072 control-byte-probed slots and inline short keys; a synchronized overflow path preserves exact equality at higher cardinality. Record IDs beyond the lookup range map to `_UNMATCHED`, including valid values through 9,999,999.

No third-party runtime dependencies. The current source is the known-good candidate preserved in official parent `6568a6794e1eea9fd0b6f6ab3cf2064ee122`. BEST is live-board run `run-955f007ac420` (T=0.084295 s, M=12,238,848 B, S=537, D=1, K=20.321199). The newer PR #7 trial failed the official Docker build (`run-7c225263b59a`); the prior source was restored and PR #7 remains open and unmerged.
