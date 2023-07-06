#ifndef PS_UTILS_KMPAUT_H
#define PS_UTILS_KMPAUT_H

template<typename T = std::string>
struct KMPAut {
    T s;
    std::size_t state_id;
    std::vector<std::size_t> pi;
    
    enum class Ret {FINAL, NON_FINAL};
    
    using value_type = T::value_type;
    
    explicit KMPAut(const T& s)
            : s(s), state_id(0), pi(s.size())
    {
        pi[0] = 0;
        std::size_t fail_idx = 0;
        
        for (std::size_t idx = 1; idx < s.size(); ++idx) {
            value_type c = s[idx];
            while (fail_idx && c != s[fail_idx]) {
                fail_idx = pi[fail_idx - 1];
            }
            if (c == s[fail_idx]) {
                fail_idx += 1;
            }
            pi[idx] = fail_idx;
        }
    }
    
    auto read(const value_type& c) -> Ret {
        const std::size_t n = s.size();
        
        while (true) {
            if (state_id < n && c == s[state_id]) {
                state_id += 1;
                break;
            }
            if (state_id == 0) {
                break;
            }
            state_id = pi[state_id - 1];
        }
        
        return state_id == s.size() ? Ret::FINAL : Ret::NON_FINAL;
    }
    
    void clear() {
        state_id = 0;
    }
};

#endif
