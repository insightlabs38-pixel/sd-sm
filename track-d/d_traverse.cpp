#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <numeric>
#include <string>
#include <thread>
#include <vector>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// Real distances stay below 2^53, so INF plus any distance cannot wrap.
// Width-128 buckets reduce far-heap traffic; re-draining preserves exactness for zero-weight edges.
static constexpr unsigned SHIFT_MAX = 7;
static constexpr uint64_t INF = uint64_t(1) << 62;

// Uninitialized, lazily faulted storage, so memory is committed only where it is written.
template <class T> struct Array {
    T* p = nullptr;
    size_t bytes = 0;
    Array() = default;
    explicit Array(size_t n, bool sparse = false) : bytes(n * sizeof(T) + 1) {
        void* q = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (q == MAP_FAILED) { perror("mmap"); std::exit(2); }
        p = static_cast<T*>(q);
        if (sparse) madvise(q, bytes, MADV_NOHUGEPAGE); // prefix-filled arrays would round up to whole huge pages
    }
    Array(Array&& o) noexcept : p(o.p), bytes(o.bytes) { o.p = nullptr; }
    Array& operator=(Array&& o) noexcept { release(); p = o.p; bytes = o.bytes; o.p = nullptr; return *this; }
    ~Array() { release(); }
    void release() { if (p) munmap(p, bytes); p = nullptr; }
    T& operator[](size_t i) { return p[i]; }
    const T& operator[](size_t i) const { return p[i]; }
};

template <class F> static void parallel(unsigned threads, F&& f) {
    std::vector<std::thread> pool;
    for (unsigned i = 1; i < threads; ++i) pool.emplace_back(f, i);
    f(0);
    for (auto& t : pool) t.join();
}

template <class F> static void blocked(unsigned threads, size_t total, F&& f) {
    parallel(threads, [&](unsigned t) { f(total * t / threads, total * (t + 1) / threads); });
}

static inline uint32_t number(const char*& p, const char* end) {
    uint32_t x = 0;
    if (end - p >= 8) {
        uint64_t w;
        memcpy(&w, p, 8);
        uint64_t stop = (w & 0xF0F0F0F0F0F0F0F0ull) ^ 0x3030303030303030ull; // nonzero byte = separator
        unsigned digits = stop ? __builtin_ctzll(stop) >> 3 : 8;
        uint64_t d = (w & 0x0F0F0F0F0F0F0F0Full) << (8 * (8 - digits));
        d = d * 10 + (d >> 8);
        d = (((d & 0x000000FF000000FFull) * 0x000F424000000064ull) + (((d >> 16) & 0x000000FF000000FFull) * 0x0000271000000001ull)) >> 32;
        x = static_cast<uint32_t>(d);
        p += digits;
    }
    while (*p >= '0' && *p <= '9') { x = x * 10 + static_cast<uint32_t>(*p - '0'); ++p; }
    ++p; // Official input has one space or LF after every integer.
    return x;
}

struct MappedFile {
    const char* data = nullptr;
    size_t size = 0;
    explicit MappedFile(const std::string& path) {
        int fd = open(path.c_str(), O_RDONLY);
        struct stat st{};
        if (fd < 0 || fstat(fd, &st) != 0) { perror(path.c_str()); std::exit(2); }
        size = static_cast<size_t>(st.st_size);
        void* q = size ? mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0) : nullptr;
        if (q == MAP_FAILED) { perror("mmap"); std::exit(2); }
        data = static_cast<const char*>(q);
        close(fd);
    }
    ~MappedFile() { if (data) munmap(const_cast<char*>(data), size); }
    // Returns page-aligned interior of [a, b) to the kernel once parsed.
    static void drop(const char* a, const char* b) {
        auto lo = (reinterpret_cast<uintptr_t>(a) + 4095) & ~uintptr_t(4095);
        auto hi = reinterpret_cast<uintptr_t>(b) & ~uintptr_t(4095);
        if (hi > lo) madvise(reinterpret_cast<void*>(lo), hi - lo, MADV_DONTNEED);
    }
};

// Search CSR with 4-byte edges: head in the high bits, weight in the low bits; weights that do not fit
// store the all-ones marker and live in a sorted escape table keyed by edge index.
static unsigned id_bits(uint64_t n) {
    unsigned bits = 1;
    while (bits < 32 && (uint64_t(1) << bits) < n) ++bits;
    return bits;
}

using Escapes = std::vector<std::pair<uint32_t, uint64_t>>;

struct Packed {
    Array<uint32_t> off, adj;
    Escapes escapes;
    unsigned wbits = 0;
    uint32_t mask = 0, dead = 0; // `dead` is a head one past the last id: an edge that leads nowhere
    Packed() = default;
    Packed(uint32_t n, size_t m) : off(size_t(n) + 1), adj(m) {
        wbits = 32 - id_bits(uint64_t(n) + 1); // room for one past the last id, used as a marker
        mask = (uint32_t(1) << wbits) - 1;
        dead = n << wbits;
    }
    void put(size_t i, uint32_t head, uint64_t w, Escapes& fresh) {
        adj[i] = head << wbits | static_cast<uint32_t>(std::min<uint64_t>(w, mask));
        if (w >= mask) fresh.push_back({i, w});
    }
    // Folds per-thread escapes (each already sorted, in ascending thread order) into the table.
    void adopt(const std::vector<Escapes>& parts) {
        for (auto& e : parts) escapes.insert(escapes.end(), e.begin(), e.end());
        std::sort(escapes.begin(), escapes.end());
    }
    uint32_t head(uint32_t e) const { return e >> wbits; }
    uint64_t escape(uint32_t i) const { return std::lower_bound(escapes.begin(), escapes.end(), std::make_pair(i, uint64_t(0)))->second; }
    uint64_t weight(uint32_t i) const {
        uint32_t w = adj[i] & mask;
        return w != mask ? w : escape(i);
    }
};

// A bin entry packs the tail's low bits with the head, so it takes 8 bytes instead of 12.
struct Entry { uint32_t key, w; };

using Run = std::pair<const Entry*, uint32_t>;

// One thread's edges partitioned by u >> shift into short chunk runs, so each bucket can later become CSR in cache.
class Binner {
    static constexpr uint32_t CHUNK = 256;
    Array<Entry> pool_;
    size_t used_ = 0;
    std::vector<Entry*> fill_, limit_;
    std::vector<std::vector<Run>> runs_;
    unsigned shift_, bits_;
    void open_chunk(size_t b) {
        close(b);
        fill_[b] = pool_.p + used_;
        limit_[b] = fill_[b] + CHUNK;
        used_ += CHUNK;
    }
    void close(size_t b) {
        if (!limit_[b]) return;
        Entry* start = limit_[b] - CHUNK;
        if (fill_[b] != start) runs_[b].push_back({start, static_cast<uint32_t>(fill_[b] - start)});
    }
public:
    Binner(unsigned shift, unsigned bits, size_t buckets, size_t max_edges)
        : pool_(max_edges + (buckets + 1) * CHUNK, true), fill_(buckets, nullptr), limit_(buckets, nullptr), runs_(buckets), shift_(shift), bits_(bits) {}
    void add(uint32_t u, uint32_t v, uint32_t w) {
        size_t b = u >> shift_;
        if (fill_[b] == limit_[b]) open_chunk(b);
        *fill_[b]++ = {static_cast<uint32_t>((uint64_t(u) & ((uint64_t(1) << shift_) - 1)) << bits_) | v, w};
    }
    void discard() { madvise(pool_.p, pool_.bytes, MADV_DONTNEED); }
    void finish() { for (size_t b = 0; b < runs_.size(); ++b) { close(b); limit_[b] = nullptr; } }
    const std::vector<Run>& runs(size_t b) const { return runs_[b]; }
};

static unsigned bucket_shift(uint32_t n) { return std::min(11u, 32 - id_bits(n)); }

// Builds CSR from the per-thread bins, one bucket at a time.
static Packed bins_to_csr(const std::vector<Binner>& bins, uint32_t n, unsigned shift, unsigned threads) {
    size_t buckets = (static_cast<size_t>(n) + (size_t(1) << shift) - 1) >> shift;
    std::vector<size_t> base(buckets + 1, 0);
    for (size_t b = 0; b < buckets; ++b) {
        base[b + 1] = base[b];
        for (const Binner& bin : bins) for (auto& run : bin.runs(b)) base[b + 1] += run.second;
    }
    Packed g(n, base[buckets]);
    std::vector<Escapes> escapes(threads);
    g.off[n] = static_cast<uint32_t>(base[buckets]);
    std::atomic<size_t> next{0};
    const unsigned bits = id_bits(n);
    const uint32_t head_mask = static_cast<uint32_t>((uint64_t(1) << bits) - 1);
    parallel(threads, [&](unsigned t) {
        std::vector<uint32_t> cursor(size_t(1) << shift);
        for (size_t b; (b = next.fetch_add(1)) < buckets;) {
            size_t lo = b << shift, hi = std::min<size_t>(n, lo + (size_t(1) << shift));
            std::fill(cursor.begin(), cursor.begin() + (hi - lo), 0);
            for (const Binner& bin : bins) for (auto& run : bin.runs(b)) for (uint32_t i = 0; i < run.second; ++i) ++cursor[uint64_t(run.first[i].key) >> bits];
            uint32_t sum = static_cast<uint32_t>(base[b]);
            for (size_t k = lo; k < hi; ++k) { uint32_t c = cursor[k - lo]; g.off[k] = cursor[k - lo] = sum; sum += c; }
            for (const Binner& bin : bins)
                for (auto& run : bin.runs(b))
                    for (uint32_t i = 0; i < run.second; ++i) {
                        const Entry& e = run.first[i];
                        uint32_t pos = cursor[uint64_t(e.key) >> bits]++;
                        g.put(pos, e.key & head_mask, e.w, escapes[t]);
                    }
        }
    });
    g.adopt(escapes);
    return g;
}

static std::vector<Binner> parse_edges(const char* begin, const char* end, uint32_t n, unsigned shift, unsigned threads) {
    std::vector<const char*> cut(threads + 1, end);
    cut[0] = begin;
    for (unsigned i = 1; i < threads; ++i) {
        const char* q = begin + static_cast<size_t>(end - begin) * i / threads;
        q = static_cast<const char*>(memchr(q, '\n', end - q));
        cut[i] = q ? q + 1 : end;
    }
    size_t buckets = (static_cast<size_t>(n) + (size_t(1) << shift) - 1) >> shift;
    std::vector<Binner> bins;
    for (unsigned t = 0; t < threads; ++t) bins.emplace_back(shift, id_bits(n), buckets, static_cast<size_t>(cut[t + 1] - cut[t]) / 6 + 1);
    parallel(threads, [&](unsigned t) {
        Binner& bin = bins[t];
        const char* p = cut[t];
        while (p < cut[t + 1]) {
            const char* block = p;
            const char* stop = std::min(cut[t + 1], p + (size_t(2) << 20));
            while (p < stop) {
                uint32_t u = number(p, end), v = number(p, end), w = number(p, end);
                bin.add(u, v, w);
            }
            MappedFile::drop(block, p);
        }
        bin.finish();
    });
    return bins;
}

struct Graph {
    uint32_t n = 0;
    Packed fwd, rev;
    Array<uint32_t> perm; // original id -> search id
};

// A raw edge whose walk through bypassable vertices is still going.
struct Walk { uint32_t edge, root, prev, at; uint64_t weight; unsigned steps; };

constexpr size_t BLOCK = 512;
using Bits = std::vector<uint64_t>;
static bool test(const Bits& bits, uint32_t v) { return bits[v >> 6] >> (v & 63) & 1; }

// Rewrites raw edges in place. A vertex with out-degree <= 2 that is not a query endpoint is skipped while exactly one
// way leads on, so only surviving heads remain; `dead` edges lead nowhere. Walks of a block advance one hop per round,
// so their cache misses overlap, and read only a snapshot of the bypassable vertices' edges.
static void bypass_edges(Packed& raw, uint32_t n, const Bits& bypass, unsigned threads) {
    Array<uint64_t> ways(n);
    blocked(threads, n, [&](size_t lo, size_t hi) {
        for (size_t x = lo; x < hi; ++x)
            if (test(bypass, x)) {
                uint32_t b = raw.off[x], e = raw.off[x + 1];
                ways[x] = (e > b ? raw.adj[b] : raw.dead) | (uint64_t(e > b + 1 ? raw.adj[b + 1] : raw.dead) << 32);
            }
    });
    std::vector<Escapes> fresh(threads);
    std::vector<std::vector<uint32_t>> stale(threads);
    parallel(threads, [&](unsigned t) {
        std::vector<Walk> walks, onward;
        std::vector<uint32_t> starts;
        size_t lo = size_t(n) * t / threads, hi = size_t(n) * (t + 1) / threads;
        for (size_t block = lo; block < hi; block += BLOCK) {
            size_t top = std::min(hi, block + BLOCK);
            uint32_t first = raw.off[block], last = raw.off[top];
            starts.resize(last - first);
            size_t count = 0;
            for (uint32_t i = first; i < last; ++i) {
                starts[count] = i;
                count += test(bypass, raw.head(raw.adj[i]));
            }
            walks.clear();
            uint32_t u = block;
            for (size_t k = 0; k < count; ++k) {
                uint32_t i = starts[k], y = raw.head(raw.adj[i]);
                while (raw.off[u + 1] <= i) ++u;
                if ((raw.adj[i] & raw.mask) == raw.mask) stale[t].push_back(i);
                if (y == u) raw.adj[i] = raw.dead;
                else walks.push_back({i, u, u, y, raw.weight(i), 0});
            }
            while (!walks.empty()) {
                for (const Walk& w : walks) __builtin_prefetch(&ways[w.at]);
                onward.clear();
                for (Walk& w : walks) {
                    uint32_t ahead = 0, next = w.at, word = 0, which = 0;
                    for (unsigned k = 0; k < 2; ++k) {
                        uint32_t e = static_cast<uint32_t>(ways[w.at] >> (32 * k));
                        if (e == raw.dead) continue;
                        uint32_t y = raw.head(e);
                        if (y != w.prev && y != w.at) { ++ahead; next = y; word = e; which = k; }
                    }
                    if (ahead > 1) { raw.put(w.edge, w.at, w.weight, fresh[t]); continue; }
                    if (ahead == 0 || next == w.root) { raw.adj[w.edge] = raw.dead; continue; }
                    w.weight += (word & raw.mask) == raw.mask ? raw.escape(raw.off[w.at] + which) : (word & raw.mask);
                    w.prev = w.at;
                    w.at = next;
                    if (!test(bypass, next) || ++w.steps == 64) raw.put(w.edge, next, w.weight, fresh[t]);
                    else onward.push_back(w);
                }
                walks.swap(onward);
            }
        }
    });
    std::vector<uint32_t> gone;
    for (auto& v : stale) gone.insert(gone.end(), v.begin(), v.end());
    std::sort(gone.begin(), gone.end());
    raw.escapes.erase(std::remove_if(raw.escapes.begin(), raw.escapes.end(),
                                     [&](auto& e) { return std::binary_search(gone.begin(), gone.end(), e.first); }),
                      raw.escapes.end());
    raw.adopt(fresh);
}

// One BFS region: nodes in discovery order and their out-degrees.
struct Region {
    Array<uint32_t> order, degree;
    uint32_t len = 0, expanded = 0;
    uint64_t edges = 0;
};

static bool take(Bits& bits, uint32_t v) {
    uint64_t bit = 1ull << (v & 63), *word = &bits[v >> 6];
    if (__atomic_load_n(word, __ATOMIC_RELAXED) & bit) return false;
    return !(__atomic_fetch_or(word, bit, __ATOMIC_RELAXED) & bit);
}

static void grow(const Packed& raw, Bits& claims, Region& r) {
    uint32_t len = r.len;
    uint64_t edges = r.edges;
    uint32_t* order = r.order.p;
    uint32_t* degree = r.degree.p;
    uint32_t head = r.expanded;
    for (; head < len; ++head) {
        if (head + 16 < len) __builtin_prefetch(&raw.off[order[head + 16]]);
        if (head + 8 < len) __builtin_prefetch(&raw.adj[raw.off[order[head + 8]]]);
        uint32_t u = order[head], live = 0;
        for (uint32_t i = raw.off[u]; i < raw.off[u + 1]; ++i) {
            if (raw.adj[i] == raw.dead) continue;
            ++live;
            if (take(claims, raw.head(raw.adj[i]))) order[len++] = raw.head(raw.adj[i]);
        }
        degree[head] = live;
        edges += live;
    }
    r.len = len;
    r.expanded = head;
    r.edges = edges;
}

// Search ids follow concurrent BFS regions grown from scattered seeds over the surviving vertices, so neighbours stay
// close in memory. Query endpoints survive; other low-degree vertices are replaced by shortcut edges.
static Graph reorder(Packed& raw, uint32_t n, const std::vector<uint8_t>& terminal, unsigned threads) {
    Graph g;
    Bits bypass((size_t(n) + 63) / 64, 0);
    blocked(threads, bypass.size(), [&](size_t lo, size_t hi) {
        for (size_t x = lo * 64; x < std::min<size_t>(n, hi * 64); ++x)
            if (!terminal[x] && raw.off[x + 1] - raw.off[x] <= 2) bypass[x >> 6] |= 1ull << (x & 63);
    });
    bypass_edges(raw, n, bypass, threads);
    Bits claims((size_t(n) + 63) / 64, 0);
    std::vector<Region> regions(threads + 1);
    for (unsigned t = 0; t <= threads; ++t) { regions[t].order = Array<uint32_t>(n, true); regions[t].degree = Array<uint32_t>(n, true); }
    for (unsigned t = 0; t < threads; ++t) {
        for (uint32_t i = 0, r = static_cast<uint32_t>(uint64_t(n) * t / threads); i < n; ++i, r = r + 1 == n ? 0 : r + 1)
            if (!test(bypass, r) && raw.off[r + 1] - raw.off[r] >= 2) {
                if (take(claims, r)) regions[t].order[regions[t].len++] = r;
                break;
            }
    }
    parallel(threads, [&](unsigned t) { grow(raw, claims, regions[t]); });
    Region& rest = regions[threads];
    for (size_t w = 0; w < claims.size(); ++w)
        for (uint64_t free = ~claims[w]; free; free &= free - 1) {
            uint32_t v = static_cast<uint32_t>(w * 64 + __builtin_ctzll(free));
            if (v < n && !test(bypass, v) && take(claims, v)) { rest.order[rest.len++] = v; grow(raw, claims, rest); }
        }

    std::vector<uint32_t> base(threads + 2, 0);
    std::vector<uint64_t> ebase(threads + 2, 0);
    for (unsigned t = 0; t <= threads; ++t) { base[t + 1] = base[t] + regions[t].len; ebase[t + 1] = ebase[t] + regions[t].edges; }
    g.n = base[threads + 1];
    Array<uint32_t> order(g.n);
    g.perm = Array<uint32_t>(n);
    g.fwd = Packed(g.n, ebase[threads + 1]);
    parallel(threads + 1, [&](unsigned t) {
        const Region& r = regions[t];
        uint64_t sum = ebase[t];
        for (uint32_t i = 0; i < r.len; ++i) {
            order[base[t] + i] = r.order[i];
            g.perm[r.order[i]] = base[t] + i;
            g.fwd.off[base[t] + i] = static_cast<uint32_t>(sum);
            sum += r.degree[i];
        }
    });
    g.fwd.off[g.n] = static_cast<uint32_t>(ebase[threads + 1]);
    regions.clear();
    std::vector<Escapes> escapes(threads);
    parallel(threads, [&](unsigned t) {
        for (size_t k = size_t(g.n) * t / threads, hi = size_t(g.n) * (t + 1) / threads; k < hi; ++k) {
            if (k + 8 < hi) __builtin_prefetch(&raw.adj[raw.off[order[k + 8]]]);
            uint32_t o = order[k], pos = g.fwd.off[k];
            for (uint32_t i = raw.off[o]; i < raw.off[o + 1]; ++i) {
                if (raw.adj[i] == raw.dead) continue;
                g.fwd.put(pos++, g.perm[raw.head(raw.adj[i])], raw.weight(i), escapes[t]);
            }
        }
    });
    g.fwd.adopt(escapes);
    return g;
}

static inline uint32_t bump(uint32_t& x) { return __atomic_fetch_add(&x, 1u, __ATOMIC_RELAXED); }

static void add_reverse(Graph& g, unsigned threads) {
    uint32_t n = g.n, m = g.fwd.off[n];
    g.rev = Packed(n, m);
    blocked(threads, m, [&](size_t lo, size_t hi) { for (size_t i = lo; i < hi; ++i) bump(g.rev.off[g.fwd.head(g.fwd.adj[i])]); });
    Array<uint32_t> cursor(n);
    std::vector<uint32_t> start(threads + 1, 0);
    parallel(threads, [&](unsigned t) {
        for (size_t k = size_t(n) * t / threads, hi = size_t(n) * (t + 1) / threads; k < hi; ++k) start[t + 1] += g.rev.off[k];
    });
    for (unsigned t = 0; t < threads; ++t) start[t + 1] += start[t];
    g.rev.off[n] = start[threads];
    parallel(threads, [&](unsigned t) {
        uint32_t sum = start[t];
        for (size_t k = size_t(n) * t / threads, hi = size_t(n) * (t + 1) / threads; k < hi; ++k) {
            uint32_t c = g.rev.off[k];
            g.rev.off[k] = cursor[k] = sum;
            sum += c;
        }
    });
    std::vector<Escapes> escapes(threads);
    parallel(threads, [&](unsigned t) {
        for (size_t u = n * size_t(t) / threads, hi = n * size_t(t + 1) / threads; u < hi; ++u)
            for (uint32_t i = g.fwd.off[u]; i < g.fwd.off[u + 1]; ++i) {
                g.rev.put(bump(cursor[g.fwd.head(g.fwd.adj[i])]), static_cast<uint32_t>(u), g.fwd.weight(i), escapes[t]);
            }
    });
    g.rev.adopt(escapes);
}

struct Query { uint32_t from, to; };

static Graph read_graph(const std::string& path, const std::vector<Query>& queries, unsigned threads) {
    MappedFile file(path);
    const char* p = file.data;
    const char* end = p + file.size;
    uint32_t n = number(p, end);
    (void)number(p, end);
    Graph g;
    {
        unsigned shift = bucket_shift(n);
        std::vector<Binner> bins = parse_edges(p, end, n, shift, threads);
        Packed raw = bins_to_csr(bins, n, shift, threads);
        parallel(threads, [&](unsigned t) { bins[t].discard(); });
        bins.clear();
        std::vector<uint8_t> terminal(n, 0);
        for (const Query& q : queries) terminal[q.from] = terminal[q.to] = 1;
        g = reorder(raw, n, terminal, threads);
    }
    add_reverse(g, threads);
    return g;
}

static std::vector<Query> read_queries(const std::string& path) {
    MappedFile file(path);
    std::vector<Query> result;
    const char* p = file.data;
    const char* end = p + file.size;
    while (p < end) {
        uint32_t s = number(p, end), t = number(p, end);
        result.push_back({s, t});
    }
    return result;
}

struct HeapNode { uint64_t distance; uint32_t node; };
// Bucketed monotone queue: width 2^shift buckets in a ring; larger jumps wait in a binary heap.
struct Heap {
    static constexpr unsigned B = 2048;
    std::array<std::vector<uint32_t>, B> bucket;
    std::array<uint64_t, B / 64> occupied{};
    std::vector<HeapNode> far;
    uint64_t cur = 0;
    size_t near = 0;
    unsigned shift = 0, node_bits = 32;
    static bool later(const HeapNode& a, const HeapNode& b) { return a.distance > b.distance; }
    void configure(uint32_t n) {
        shift = std::min(SHIFT_MAX, 32 - id_bits(n));
        node_bits = 32 - shift;
    }
    void clear() {
        for (size_t w = 0; w < occupied.size(); ++w)
            for (uint64_t bits = occupied[w]; bits; bits &= bits - 1) bucket[w * 64 + __builtin_ctzll(bits)].clear();
        occupied.fill(0);
        far.clear();
        cur = 0;
        near = 0;
    }
    void push(uint64_t d, uint32_t v) {
        if ((d >> shift) - cur >= B) { far.push_back({d, v}); std::push_heap(far.begin(), far.end(), later); return; }
        unsigned b = (d >> shift) & (B - 1);
        bucket[b].push_back(v | static_cast<uint32_t>((d & ((uint64_t(1) << shift) - 1)) << node_bits));
        occupied[b >> 6] |= 1ull << (b & 63);
        ++near;
    }
    // Positions cur on the first nonempty bucket and returns its smallest possible key; INF if empty.
    uint64_t lower_bound() {
        if (near) {
            unsigned b = cur & (B - 1), w = b >> 6;
            uint64_t bits = occupied[w] & (~0ull << (b & 63));
            while (!bits) { w = (w + 1) & (B / 64 - 1); bits = occupied[w]; }
            cur += (((w << 6) | __builtin_ctzll(bits)) - b) & (B - 1);
        } else if (!far.empty()) {
            cur = far.front().distance >> shift;
        } else {
            return INF;
        }
        while (!far.empty() && (far.front().distance >> shift) - cur < B) {
            HeapNode x = far.front();
            std::pop_heap(far.begin(), far.end(), later);
            far.pop_back();
            push(x.distance, x.node);
        }
        return cur << shift;
    }
};

// Distances live in fixed pages materialized on first write and recycled per query, so memory tracks the search, not n.
class Distances {
    static constexpr unsigned SHIFT = 7, SIZE = 1u << SHIFT;
    std::vector<uint64_t*> dir_;
    std::vector<uint32_t> used_;
    std::vector<std::unique_ptr<uint64_t[]>> store_; // the first used_.size() pages are in use
    std::array<uint64_t, SIZE> blank_;
    uint64_t* acquire(uint32_t page) {
        if (used_.size() == store_.size()) store_.emplace_back(new uint64_t[SIZE]);
        uint64_t* p = store_[used_.size()].get();
        std::fill(p, p + SIZE, INF);
        used_.push_back(page);
        return dir_[page] = p;
    }
public:
    explicit Distances(uint32_t n) : dir_((n >> SHIFT) + 1) { blank_.fill(INF); std::fill(dir_.begin(), dir_.end(), blank_.data()); }
    uint64_t get(uint32_t v) const { return dir_[v >> SHIFT][v & (SIZE - 1)]; }
    // Lowers the label of v to d if that improves it.
    bool lower(uint32_t v, uint64_t d) {
        uint64_t* p = dir_[v >> SHIFT];
        if (d >= p[v & (SIZE - 1)]) return false;
        if (p == blank_.data()) p = acquire(v >> SHIFT);
        p[v & (SIZE - 1)] = d;
        return true;
    }
    void reset() {
        for (uint32_t page : used_) dir_[page] = blank_.data();
        used_.clear();
    }
};

struct Side {
    const Packed& csr;
    Distances dist;
    Heap heap;
    Side(const Packed& c, uint32_t n) : csr(c), dist(n) { heap.configure(n); }
    void start(uint32_t s) { dist.reset(); heap.clear(); dist.lower(s, 0); heap.push(0, s); }
    // Settles every vertex of the current bucket (re-draining entries it adds) and returns how many were expanded.
    size_t drain(const Side& other, uint64_t& best) {
        std::vector<uint32_t>& bk = heap.bucket[heap.cur & (Heap::B - 1)];
        const uint64_t base = heap.cur << heap.shift;
        const unsigned nbits = heap.node_bits, wbits = csr.wbits;
        const uint32_t node_mask = static_cast<uint32_t>((uint64_t(1) << nbits) - 1), wmask = csr.mask;
        const uint32_t* off = csr.off.p;
        const uint32_t* adj = csr.adj.p;
        size_t count = 0;
        while (!bk.empty()) {
            uint32_t entry = bk.back();
            bk.pop_back();
            --heap.near;
            uint32_t u = entry & node_mask;
            uint64_t d = base | (uint64_t(entry) >> nbits);
            if (dist.get(u) != d) continue;
            ++count;
            for (uint32_t i = off[u], last = off[u + 1]; i < last; ++i) {
                uint32_t e = adj[i], v = e >> wbits;
                uint64_t w = e & wmask;
                if (w == wmask) w = csr.weight(i);
                uint64_t nd = d + w;
                if (dist.lower(v, nd)) {
                    heap.push(nd, v);
                    uint64_t meet = nd + other.dist.get(v);
                    if (meet < best) best = meet;
                }
            }
        }
        unsigned b = heap.cur & (Heap::B - 1);
        heap.occupied[b >> 6] &= ~(1ull << (b & 63));
        return count;
    }
};

struct Worker {
    Side fwd, bwd;
    uint32_t probe;
    Worker(const Graph& g, uint32_t p) : fwd(g.fwd, g.n), bwd(g.rev, g.n), probe(p) {}
    int64_t solve(uint32_t s, uint32_t t) {
        if (s == t) return 0;
        if (fwd.csr.off[s] == fwd.csr.off[s + 1] || bwd.csr.off[t] == bwd.csr.off[t + 1]) return -1;
        bwd.dist.reset();
        fwd.start(s);
        uint64_t best = INF;
        for (size_t settled = 0; settled < probe;) {
            uint64_t f = fwd.heap.lower_bound();
            uint64_t known = fwd.dist.get(t);
            if (known < f) return static_cast<int64_t>(known);
            if (f == INF) return -1;
            settled += fwd.drain(bwd, best);
        }
        bwd.start(t);
        best = std::min(best, fwd.dist.get(t));
        for (;;) {
            uint64_t f = fwd.heap.lower_bound(), b = bwd.heap.lower_bound();
            if (f == INF || b == INF || f + b >= best) break;
            if (f <= b) fwd.drain(bwd, best); else bwd.drain(fwd, best);
        }
        return best == INF ? -1 : static_cast<int64_t>(best);
    }
};

static void write_results(const std::string& path, const std::vector<int64_t>& answers) {
    std::string text;
    text.reserve(answers.size() * 12);
    for (int64_t x : answers) text += std::to_string(x) + '\n';
    FILE* f = fopen(path.c_str(), "wb");
    if (!f || fwrite(text.data(), 1, text.size(), f) != text.size() || fclose(f) != 0) { perror(path.c_str()); std::exit(2); }
}

static std::string option(const char* name, const char* fallback) {
    const char* v = getenv(name);
    return v ? v : fallback;
}

int main() {
    std::string data = option("SD_DATA", "/data"), out = option("SD_OUT", "/out");
    unsigned threads = std::min(12u, std::max(1u, std::thread::hardware_concurrency()));
    if (getenv("SD_THREADS")) threads = std::max(1, std::min(64, atoi(getenv("SD_THREADS"))));
    uint32_t probe = std::max(0, atoi(option("SD_PROBE", "256").c_str()));
    std::vector<Query> queries = read_queries(data + "/queries.txt");
    unsigned build_threads = std::min(threads, 4u);
    if (getenv("SD_BUILD_THREADS")) build_threads = std::min(threads, static_cast<unsigned>(std::max(1, atoi(getenv("SD_BUILD_THREADS")))));
    Graph g = read_graph(data + "/graph.txt", queries, build_threads);
    for (Query& q : queries) { q.from = g.perm[q.from]; q.to = g.perm[q.to]; }
    g.perm.release();
    std::vector<int64_t> answers(queries.size(), -1);
    std::vector<uint32_t> schedule(queries.size());
    std::iota(schedule.begin(), schedule.end(), 0);
    std::sort(schedule.begin(), schedule.end(), [&](uint32_t a, uint32_t b) { return queries[a].from < queries[b].from; });
    std::atomic<size_t> next{0};
    parallel(std::min<size_t>(threads, std::max<size_t>(1, queries.size())), [&](unsigned) {
        Worker worker(g, probe);
        for (size_t k; (k = next.fetch_add(1, std::memory_order_relaxed)) < queries.size();) {
            uint32_t i = schedule[k];
            answers[i] = worker.solve(queries[i].from, queries[i].to);
        }
    });
    write_results(out + "/distances.txt", answers);
}
