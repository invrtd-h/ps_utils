#define LOCAL
#include "include/init.h"
using ugly::dout;
using ugly::fmt;
#include <bits/stdc++.h>
#include "solve.cpp"

#ifdef LOCAL

namespace chr = std::chrono;
using hrc = chr::high_resolution_clock;

int main() {
    std::string read_mode;
    
    freopen("../input.txt", "r", stdin);
    
    for (int i = 0; i < (1 << 30); ++i) {
        if (!(std::cin >> read_mode)) {
            break;
        }
        auto start = hrc::now();
        solve();
        auto end = hrc::now();
        auto time_diff = (double) (end - start).count();
        time_diff /= 1'000'000'000;
        
        std::stringstream ss;
        ss << std::fixed << std::setprecision(4) << time_diff;
        
        std::cout << ugly::fmt("====== exec {}: {}s ======",
                               i, ss.str()) << std::endl;
    }
}

#endif
