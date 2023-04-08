#ifndef PS_UTILS_UTIL_H
#define PS_UTILS_UTIL_H

#include <bits/stdc++.h>

/**
 * a trivial function.
 * @param s
 * @param delim
 * @return
 */
auto split(const std::string& s, char delim='\n') {
    std::istringstream iss(s);
    std::string temp;
    std::vector<std::string> ret;
    
    while (std::getline(iss, temp, delim)) {
        ret.push_back(std::move(temp));
    }
    
    return ret;
}

/**
 * A friend injection implementation.
 * @tparam member
 */
template<auto member>
struct Stealer {
    friend auto& data_getter(std::stack<int>& s) {
        return s.*member;
    }
};

template struct Stealer<&std::stack<int>::c>;
auto& data_getter(std::stack<int>& s);

#endif
