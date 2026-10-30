# Track A performance log

## Initial exact C++ baseline, October 30, 2026

- Design: single mmap parse, endpoint interning, count/scatter, exact local sorting or multiselect.
- Local compiler: GCC 14.2, `-O3 -std=c++20 -static-libstdc++ -static-libgcc`.
- Synthetic differential tests: 12 cases covering empty and small files, 1,000 to 310,000 records, four seeds, unsigned-32-bit latency extremes, duplicated lines, all status classes, month/hour boundaries, and endpoint ordering. All passed against a Python integer oracle.
- Local 310,000-record synthetic run: 0.05 s wall and 36,544 KiB peak RSS on the available development container. This is **not** an official benchmark or a scoring-box measurement.
- Official public seed-1 and holdout hashes: pending GitHub CI. No board run ID exists yet; Luna records actual board IDs after integration.

## Integrator validation, October 30, 2026

- Candidate source: `sd-ta` remote HEAD `3d32b31c4fb32258f1a1b11828ea21e633147d5c`.
- Developer synthetic differential suite: 12 cases across four seeds, including empty input and uint32 latency extremes; all passed.
- Organizer generator/reference: seed-1 `tiny`, `sample`, and `full` outputs, plus seed-42 `sample`, matched byte-for-byte. Sample SHA-256 `ca6311bbeb536fa55d85265bf6fd3d24cc9586f13de1ac73bd2a23ac3893aac3`; full SHA-256 `495ca09682b9673ef836a506496177680bb4a3af54255174befddb1f83481cd3` (also matches the published full-data hash).
- Offline allowlisted Docker build passed; image size 79 MB. Full-data sandbox run passed with the required single output file and exact hash. Local container elapsed time 1.09 s including startup; `memory.peak` 40,443,904 bytes. Seed-42 sample SHA-256 `835c36377118af19264750c9b1031225ead44a8555e913c22d31a827dbe486c8`. These are local checks, not board measurements.
- Board run IDs: none yet; submission repo is not registered and the board app is not confirmed installed. No official score claimed.
