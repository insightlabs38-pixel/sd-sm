# Track D: Traverse

Exact directed shortest-path distances with CSR and bidirectional Dijkstra using a monotone 64-bit radix heap. The bounded forward probe continues into bidirectional search without discarding settled state. Per-query scratch uses 8-bit generation stamps with exact wrap resets; parser scratch is released after CSR construction. Independent workers preserve query order.

Current source passed the 66,000-query epoch-wrap regression, 83 differential cases, official full output hash and restricted Docker comparison in [CI run 41110514088](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41110514088). Timing and memory evidence is in [PERF.md](PERF.md); CI numbers are not official board results.

No third-party runtime dependencies; build uses the pinned, organizer-allowlisted GCC image.
