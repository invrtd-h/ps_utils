#include "../include/init.h"
using ugly::dout;
using ugly::fmt;

#include "solve.h"

#ifndef ONLINE_JUDGE
#ifndef FUNC_IMPL

namespace chr = std::chrono;
using hrc = chr::high_resolution_clock;

int main() {
    std::string read_mode;
    
    for (int i = 0; i < (1 << 30); ++i) {
        if (!(std::cin >> read_mode)) {
            break;
        }
        auto start = hrc::now();
        try {
            solve();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
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
#endif