# Track C: Join

A C++17 byte-oriented parser reads the hostile CSV and region lookup, then aggregates exact country statistics. It preserves quoted fields, escaped quotes, embedded newlines, BOM placement, CRLF/LF handling, integer cents, and unmatched regions. Parallel workers use bounded pending batches and exact name interning; consumed mmap pages are reclaimed after names are copied into stable storage. Output is ordered by country, with `_UNMATCHED` last. Runtime dependencies are limited to the C++ standard library and system C runtime.
