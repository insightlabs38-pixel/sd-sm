# Track C: Join

Dependency-free C++17 parser and exact aggregator for Track C. It handles quoted fields and escaped quotes, preserves exact name identity, and maps unknown record region IDs through the frozen input range to `_UNMATCHED`.

Current candidate source from `sd-tc` main is blob `4ca129b0ca9596554d052aadb9d5e751496cc754`; matching source passed developer CI [41229750254]. Its first official build attempt (`run-ab5d43ee092f`) failed. Public Dockerfiles show the official compile omitted the `-march=x86-64-v3` flag used by the verified developer build; the submission Dockerfile now matches that tested flag for retest. Known-good source blob `7def6ac05e18fcf871310f37abade9ca1a904760` remains in parent `f0e8236ee3641950287d6e2dd25814fb4b6ef9bb` for rollback. Official scoring is pending.
