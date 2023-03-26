#ifndef PS_UTILS_DISJOINT_SET_H
#define PS_UTILS_DISJOINT_SET_H

constexpr int NN = 100'000;

struct DJS_halving {
    int parent[NN];
    
    void init() noexcept {
        for (int i = 0; i < NN; ++i) {
            parent[i] = i;
        }
    }
    int find(int idx) noexcept {
        while (idx != parent[idx]) {
            idx = parent[idx] = parent[parent[idx]];
        }
        return idx;
    }
    void join(int l, int r) noexcept {
        int pl = find(l), pr = find(r);
        parent[pr] = pl;
    }
};

#endif
