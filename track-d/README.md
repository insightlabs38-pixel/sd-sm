# Track D: Traverse

Exact directed shortest-path distances using CSR storage, a bounded forward search for short paths, and bidirectional Dijkstra for longer paths. The queue is a 64-bit monotone radix heap whose buckets are redistributed in place. Independent workers keep per-query distance state; answers are written in input order.

## Validation

The official full seed-1 output matches SHA-256 `a23dbdf0a3e49cc8901310a9ee1dc6a9a569a85297b6da75c2a7002cb2ed277e`. Developer CI run [41085036796](https://github.com/insightlabs38-pixel/sd-td/actions/runs/41085036796) passed official generated cases, differential tests, and pinned offline Docker execution. Its runtime and memory figures are GitHub-runner measurements, not board scores.

No third-party runtime dependencies; build uses the pinned, organizer-allowlisted GCC image.
