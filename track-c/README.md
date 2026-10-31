# Track C: Join

A byte-oriented C++17 implementation parses the hostile CSV and aggregates exact name/region groups. It maps unknown record region IDs through the frozen input range up to 9,999,999 to `_UNMATCHED`; exact name comparisons and the synchronized overflow path preserve correctness. No third-party runtime dependencies.

The current source is the known-good candidate restored from parent `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21` (blob `7def6ac05e18fcf871310f37abade9ca1a904760`). BEST/LATEST is `run-8f98e6ec4091` (T=0.082831 s, M=12,500,992 B, S=537, D=1, K=20.413289). PR #8's official trial failed Docker build (`run-adcadeec9db2`); its candidate remains in commit `5b1f942cac523c62dcda40eca63586732c6a7959`, and the PR remains open and unmerged.
