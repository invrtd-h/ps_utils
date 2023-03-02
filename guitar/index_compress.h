#ifndef PS_UTILS_INDEX_COMPRESS_H
#define PS_UTILS_INDEX_COMPRESS_H

#include <bits/stdc++.h>

struct Compressor {
    std::unordered_map<int, int> compressed_ids;
    std::vector<int> raw_ids;
    
    explicit Compressor(std::vector<int> vec) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        
        for (int i = 0; i < vec.size(); ++i) {
            compressed_ids[vec[i]] = i;
        }
        
        raw_ids = std::move(vec);
    }
    
    int get_compressed_id(int raw_id) {
        return compressed_ids[raw_id];
    }
    
    int get_raw_id(int compressed_id) const {
        return raw_ids[compressed_id];
    }
};

#endif
