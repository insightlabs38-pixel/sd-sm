#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct MappedFile {
    int fd = -1;
    size_t size = 0;
    const char* data = nullptr;
    explicit MappedFile(const std::string& path) {
        fd = open(path.c_str(), O_RDONLY);
        if (fd < 0) { perror(path.c_str()); std::exit(2); }
        struct stat st{};
        if (fstat(fd, &st) != 0) { perror("fstat"); std::exit(2); }
        size = static_cast<size_t>(st.st_size);
        if (size) {
            void* p = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
            if (p == MAP_FAILED) { perror("mmap"); std::exit(2); }
            data = static_cast<const char*>(p);
        }
    }
    ~MappedFile() { if (data) munmap(const_cast<char*>(data), size); if (fd >= 0) close(fd); }
    MappedFile(const MappedFile&) = delete;
    MappedFile& operator=(const MappedFile&) = delete;
};

static inline uint32_t number(const char*& p) {
    uint32_t x = 0;
    while (*p >= '0' && *p <= '9') { x = x * 10 + static_cast<uint32_t>(*p - '0'); ++p; }
    ++p; // Official input has one space or LF after every integer.
    return x;
}

struct Edge { uint32_t to, weight; };
struct Triple { uint32_t from, to, weight; };
struct Query { uint32_t from, to; };
struct Graph {
    uint32_t n;
    std::vector<uint32_t> offsets, indegree;
    std::vector<Edge> edges;
    std::vector<uint32_t> reverse_offsets;
    std::vector<Edge> reverse_edges;
};

static Graph read_graph(const std::string& path, bool two_pass, bool bidirectional) {
    MappedFile file(path);
    const char* begin = file.data;
    const char* p = begin;
    const uint32_t n = number(p), m = number(p);
    Graph g;
    g.n = n;
    g.offsets.assign(static_cast<size_t>(n) + 1, 0);
    g.indegree.assign(n, 0);
    std::vector<Triple> triples;
    if (!two_pass) triples.reserve(m);
    for (uint32_t i = 0; i < m; ++i) {
        uint32_t u = number(p), v = number(p), w = number(p);
        ++g.offsets[u + 1];
        ++g.indegree[v];
        if (!two_pass) triples.push_back({u, v, w});
    }
    for (uint32_t i = 1; i <= n; ++i) g.offsets[i] += g.offsets[i - 1];
    g.edges.resize(m);
    std::vector<uint32_t> cursor(g.offsets.begin(), g.offsets.end() - 1);
    if (two_pass) {
        p = begin;
        (void)number(p); (void)number(p);
        for (uint32_t i = 0; i < m; ++i) {
            uint32_t u = number(p), v = number(p), w = number(p);
            g.edges[cursor[u]++] = {v, w};
        }
    } else {
        for (const Triple& e : triples) g.edges[cursor[e.from]++] = {e.to, e.weight};
    }
    if (bidirectional) {
        g.reverse_offsets.assign(static_cast<size_t>(n) + 1, 0);
        for (uint32_t i = 0; i < n; ++i) g.reverse_offsets[i + 1] = g.reverse_offsets[i] + g.indegree[i];
        g.reverse_edges.resize(m);
        std::vector<uint32_t> rpos(g.reverse_offsets.begin(), g.reverse_offsets.end() - 1);
        for (uint32_t u = 0; u < n; ++u)
            for (uint32_t i = g.offsets[u]; i < g.offsets[u + 1]; ++i) {
                const Edge& e = g.edges[i];
                g.reverse_edges[rpos[e.to]++] = {u, e.weight};
            }
    }
    return g;
}

static std::vector<Query> read_queries(const std::string& path) {
    MappedFile file(path);
    std::vector<Query> result;
    const char* p = file.data;
    const char* end = p + file.size;
    while (p < end) {
        uint32_t s = number(p), t = number(p);
        result.push_back({s, t});
    }
    return result;
}

struct HeapNode { uint64_t distance; uint32_t node; };
struct Heap {
    std::array<std::vector<HeapNode>, 65> buckets;
    uint64_t last = 0;
    size_t count = 0;
    inline static unsigned index(uint64_t x) { return x ? 64 - __builtin_clzll(x) : 0; }
    void reserve(size_t) {}
    void clear() {
        for (auto& b : buckets) b.clear();
        last = 0;
        count = 0;
    }
    bool empty() const { return count == 0; }
    void push(uint64_t d, uint32_t v) {
        buckets[index(d ^ last)].push_back({d, v});
        ++count;
    }
    void prepare() {
        if (!buckets[0].empty()) return;
        unsigned i = 1;
        while (i < 65 && buckets[i].empty()) ++i;
        if (i == 65) std::abort();
        uint64_t minimum = std::numeric_limits<uint64_t>::max();
        for (const auto& e : buckets[i]) minimum = std::min(minimum, e.distance);
        last = minimum;
        for (const auto& e : buckets[i]) buckets[index(e.distance ^ last)].push_back(e);
        buckets[i].clear();
    }
    const HeapNode& top() { prepare(); return buckets[0].back(); }
    HeapNode pop() {
        prepare();
        HeapNode e = buckets[0].back();
        buckets[0].pop_back();
        --count;
        return e;
    }
};

struct Worker {
    const Graph& graph;
    std::vector<uint64_t> distance;
    std::vector<uint32_t> stamp;
    uint32_t epoch = 0;
    uint32_t probe = 0;
    Heap heap;
    Heap backward_heap;
    std::vector<uint64_t> backward_distance;
    std::vector<uint32_t> backward_stamp;
    explicit Worker(const Graph& g, uint32_t p) : graph(g), distance(g.n), stamp(g.n, 0), probe(p) {
        heap.reserve(16384);
        if (!graph.reverse_edges.empty()) {
            backward_distance.resize(g.n);
            backward_stamp.resize(g.n, 0);
            backward_heap.reserve(16384);
        }
    }
    int64_t solve_bidirectional(uint32_t s, uint32_t t) {
        if (s == t) return 0;
        if (graph.offsets[s] == graph.offsets[s + 1] || graph.indegree[t] == 0) return -1;
        if (++epoch == 0) {
            std::fill(stamp.begin(), stamp.end(), 0);
            std::fill(backward_stamp.begin(), backward_stamp.end(), 0);
            epoch = 1;
        }
        heap.clear();
        backward_heap.clear();
        stamp[s] = backward_stamp[t] = epoch;
        distance[s] = backward_distance[t] = 0;
        heap.push(0, s);
        backward_heap.push(0, t);
        uint64_t best = std::numeric_limits<uint64_t>::max();
        for (;;) {
            while (!heap.empty()) {
                const HeapNode& x = heap.top();
                if (stamp[x.node] == epoch && distance[x.node] == x.distance) break;
                heap.pop();
            }
            while (!backward_heap.empty()) {
                const HeapNode& x = backward_heap.top();
                if (backward_stamp[x.node] == epoch && backward_distance[x.node] == x.distance) break;
                backward_heap.pop();
            }
            if (heap.empty() || backward_heap.empty()) break;
            uint64_t f = heap.top().distance, b = backward_heap.top().distance;
            if (f + b >= best) break;
            bool forward = f <= b;
            Heap& pq = forward ? heap : backward_heap;
            std::vector<uint64_t>& dist = forward ? distance : backward_distance;
            std::vector<uint32_t>& seen = forward ? stamp : backward_stamp;
            const std::vector<uint64_t>& other_dist = forward ? backward_distance : distance;
            const std::vector<uint32_t>& other_seen = forward ? backward_stamp : stamp;
            const std::vector<uint32_t>& off = forward ? graph.offsets : graph.reverse_offsets;
            const std::vector<Edge>& edges = forward ? graph.edges : graph.reverse_edges;
            HeapNode top = pq.pop();
            uint32_t u = top.node;
            uint64_t d = top.distance;
            if (other_seen[u] == epoch) best = std::min(best, d + other_dist[u]);
            for (uint32_t i = off[u], e = off[u + 1]; i < e; ++i) {
                const Edge& edge = edges[i];
                uint32_t v = edge.to;
                uint64_t nd = d + edge.weight;
                if (seen[v] != epoch || nd < dist[v]) {
                    seen[v] = epoch;
                    dist[v] = nd;
                    pq.push(nd, v);
                    if (other_seen[v] == epoch) best = std::min(best, nd + other_dist[v]);
                }
            }
        }
        return best == std::numeric_limits<uint64_t>::max() ? -1 : static_cast<int64_t>(best);
    }
    int64_t solve(uint32_t s, uint32_t t) {
        if (!graph.reverse_edges.empty()) {
            if (probe) {
                int64_t r = solve_forward(s, t, probe);
                if (r != -2) return r;
            }
            return solve_bidirectional(s, t);
        }
        return solve_forward(s, t, std::numeric_limits<uint32_t>::max());
    }
    int64_t solve_forward(uint32_t s, uint32_t t, uint32_t max_settles) {
        if (s == t) return 0;
        if (graph.offsets[s] == graph.offsets[s + 1] || graph.indegree[t] == 0) return -1;
        if (++epoch == 0) { std::fill(stamp.begin(), stamp.end(), 0); epoch = 1; }
        heap.clear();
        stamp[s] = epoch;
        distance[s] = 0;
        heap.push(0, s);
        uint32_t settled = 0;
        while (!heap.empty()) {
            HeapNode top = heap.pop();
            uint32_t u = top.node;
            uint64_t d = top.distance;
            if (stamp[u] != epoch || d != distance[u]) continue;
            if (u == t) return static_cast<int64_t>(d);
            if (++settled >= max_settles) return -2;
            for (uint32_t i = graph.offsets[u], e = graph.offsets[u + 1]; i < e; ++i) {
                const Edge& edge = graph.edges[i];
                uint64_t nd = d + edge.weight;
                uint32_t v = edge.to;
                if (stamp[v] != epoch || nd < distance[v]) {
                    stamp[v] = epoch;
                    distance[v] = nd;
                    heap.push(nd, v);
                }
            }
        }
        return -1;
    }
};

static void write_results(const std::string& path, const std::vector<int64_t>& answers) {
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) { perror(path.c_str()); std::exit(2); }
    char buffer[32768];
    setvbuf(f, buffer, _IOFBF, sizeof(buffer));
    for (int64_t x : answers) fprintf(f, "%lld\n", static_cast<long long>(x));
    if (fclose(f) != 0) { perror("fclose"); std::exit(2); }
}

int main() {
    const char* env_data = getenv("SD_DATA");
    const char* env_out = getenv("SD_OUT");
    std::string data = env_data ? env_data : "/data";
    std::string out = env_out ? env_out : "/out";
    bool two_pass = getenv("SD_TWO_PASS") && strcmp(getenv("SD_TWO_PASS"), "0") != 0;
    bool bidi = !getenv("SD_BIDI") || strcmp(getenv("SD_BIDI"), "0") != 0;
    Graph g = read_graph(data + "/graph.txt", two_pass, bidi);
    std::vector<Query> queries = read_queries(data + "/queries.txt");
    std::vector<int64_t> answers(queries.size(), -1);
    unsigned threads = 4;
    if (const char* env = getenv("SD_THREADS")) threads = std::max(1, std::min(16, atoi(env)));
    threads = std::min<unsigned>(threads, static_cast<unsigned>(std::max<size_t>(1, queries.size())));
    std::atomic<size_t> next{0};
    uint32_t probe = 256;
    if (const char* env = getenv("SD_PROBE")) probe = static_cast<uint32_t>(std::max(0, atoi(env)));
    auto run = [&]() {
        Worker worker(g, probe);
        for (;;) {
            size_t i = next.fetch_add(1, std::memory_order_relaxed);
            if (i >= queries.size()) break;
            answers[i] = worker.solve(queries[i].from, queries[i].to);
        }
    };
    std::vector<std::thread> workers;
    for (unsigned i = 1; i < threads; ++i) workers.emplace_back(run);
    run();
    for (auto& thread : workers) thread.join();
    write_results(out + "/distances.txt", answers);
}
