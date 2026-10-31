# Track C: Join

A byte-oriented C++17 parser handles hostile quoted CSV and maps lookup regions through a dense table. Six workers share an exact-name table with 131,072 control-byte-probed slots and inline short keys; a synchronized overflow path preserves exact equality at higher cardinality. Record IDs beyond the lookup range map to `_UNMATCHED`, including valid values through 9,999,999.

No third-party runtime dependencies. The current source is an unscored low-memory candidate from open PR #5; official promotion depends on the pending scoring-box result.
