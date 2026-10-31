# Track C: Join

A byte-oriented C++17 implementation parses the hostile CSV, aggregates exact name/region groups, and maps unknown record region IDs above 999,999 to `_UNMATCHED` within the frozen input range through 9,999,999. It retains exact name comparisons and the synchronized overflow path. No third-party runtime dependencies.

The current official known-good source is retained in parent `9b821f5451c9cd19fa5e04b3db4d99b3af5a2b21` (BEST `run-955f007ac420`, K=20.321199; most recent same-source run `run-2834c7216378`, K=20.213758). A trial of open `sd-tc` PR #8 is staged from source blob `11bfcc0ba501d22454a8f21a06e23ad020183efd`; developer CI passed, while official scoring is pending. PR #8 will be merged only if the official trial qualifies.
