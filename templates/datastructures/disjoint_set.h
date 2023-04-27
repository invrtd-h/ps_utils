#ifndef PS_UTILS_DISJOINT_SET_H
#define PS_UTILS_DISJOINT_SET_H

#include <bits/stdc++.h>

struct DJS {
    std::vector<int> parent;
    
    explicit DJS(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int idx) {
        while (idx != parent[idx]) {
            idx = parent[idx] = parent[parent[idx]];
        }
        return idx;
    }
    
    void join(int l, int r) {
        int pl = find(l), pr = find(r);
        parent[pr] = pl;
    }
    
    bool joined(int l, int r) {
        int pl = find(l), pr = find(r);
        return pl == pr;
    }
};

#endif
