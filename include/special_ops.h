#ifndef PS_UTILS_SPECIAL_OPS_H
#define PS_UTILS_SPECIAL_OPS_H

#include <concepts>
#include <functional>
#include <ranges>

template<typename T, std::invocable<T> F>
constexpr auto operator>>(T&& t, F&& f) {
    return std::invoke(std::forward<F>(f), std::forward<T>(t));
}

namespace ran = std::ranges;
namespace vw = std::views;

#endif
