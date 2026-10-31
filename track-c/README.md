# Track C: Join

A byte-oriented C++17 CSV parser aggregates exact name/region groups with six workers. This trial combines certified input splitting, wide CRC32C name-tail hashing, and guarded SWAR integer decoding with the compact inline-name table. Exact comparisons and the synchronized overflow path preserve correctness for high-cardinality names; record IDs outside the lookup table map to `_UNMATCHED`, including valid IDs through 9,999,999.

No third-party runtime dependencies. Candidate from open `sd-tc` PR #7 (`dcb50168fcfb8b8b75b6eebc8c03976c589d056e`), source blob `dc7d92e9f2ab8e30bbd7b90a69360e22648c939a`, is staged for official scoring. Developer exactness, sanitizer, Docker, and sandbox checks passed; official T/M/S/D/K are pending. The prior PR #5 source remains in parent commit `6568a6794e1eea9fd0b6f6ab3cf2064ee34ee122` for rollback.
