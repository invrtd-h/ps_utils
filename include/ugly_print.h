#ifndef UGLY_PRINT_UGLY_PRINT_20_H
#define UGLY_PRINT_UGLY_PRINT_20_H

#include <concepts>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <utility>
#include <regex>
#include <typeinfo>

/**
 * str_cat function implementation.\n
 *
 * It is a cat made by string. We want to make the string concatenation
 * faster using this function. (In previous version, we used std::stringstream
 * and it was slow.)
 */
namespace ugly::detail {
    
    /**
     * A template guide for tracking template deductions.\n\n
     * How to use:
     * Since this class is not defined,
     *
     */
    template<typename>
    class [[maybe_unused]] TD;
    
    
    [[maybe_unused]]
    inline std::size_t str_len(const std::string& str) noexcept {
        return str.size();
    }
    
    [[maybe_unused]]
    inline constexpr std::size_t str_len(const char* str) noexcept {
        std::size_t ret = 0;
        while (str[ret]) {
            ret++;
        }
        return ret;
    }
    
    static_assert(str_len("what") == 4);
    
    template<std::convertible_to<std::string>... T>
    inline std::string str_cat(const T&... strs) {
        std::size_t size = (str_len(std::string(strs)) + ...);
        std::string ret;
        ret.reserve(size);
        
        (ret.append(strs), ...);
        
        return ret;
    }
    
    constexpr inline auto str_repetition(const std::string& s, std::size_t time) -> std::string {
        std::string ret;
        ret.reserve(s.size() * time);
        
        for (std::size_t i = 0; i < time; ++i) {
            ret += s;
        }
        
        return ret;
    }
}

/**
 * to_str function declaration.
 */
namespace ugly::detail {
    /**
     * Universal to_str function.
     * @return std::string object that represents that object.
     */
    template<typename T>
    auto to_str(const T&) -> std::string;
}

/**
 * Definitions for some basic rules.
 * If there is any basic rule for printing,
 * the rule precedes any other rules.
 */
namespace ugly::detail {
    template<typename U1, typename U2>
    auto to_str_basic(const std::pair<U1, U2>& t) -> std::string {
        return str_cat("<", to_str(t.first), ", ", to_str(t.second), ">");
    }
    
    template<typename T>
    [[maybe_unused]]
    auto to_str_basic(std::stack<T> t) -> std::string {
        if (t.empty()) {
            return "[]";
        }
        
        std::string ret("[");
        
        while (!t.empty()) {
            ret += to_str(t.top());
            ret += " > ";
            t.pop();
        }
        
        ret.pop_back();
        ret.pop_back();
        ret.back() = ']';
        
        return ret;
    }
    
    template<typename T>
    [[maybe_unused]]
    auto to_str_basic(std::queue<T> t) -> std::string {
        if (t.empty()) {
            return "[]";
        }
        
        std::string ret("[");
        
        while (!t.empty()) {
            ret += to_str(t.front());
            ret += " > ";
            t.pop();
        }
        
        ret.pop_back();
        ret.pop_back();
        ret.back() = ']';
        
        return ret;
    }
}

/**
 * Definitions for some concepts.
 */
namespace ugly::detail {
    
    template<typename T>
    concept basic_rule_defined = requires (T t) {
        to_str_basic(t);
    };
    
    template<typename T>
    concept printable = requires (T t) {
        std::cout << t;
    };
    
    /**
     * A container concept.\n
     * If t.begin() and t.end() is legal expression,
     * then t is a container.
     * @tparam T tparam
     */
    template<typename T>
    concept container = requires (T t) {
        t.begin();
        t.end();
    };
    
    /**
     * A concept for naive arrays.
     * @tparam T tparam
     */
    template<typename T>
    concept array = std::is_array_v<T>;
    
    template<typename T>
    concept named_tuple = requires {
        T::mem_names;
    };
    
    template<typename T>
    concept unpackable = requires {
        T::mem_num;
    };
}

namespace ugly::detail {
    template<container T>
    struct container_dim {
        using value_type = std::decay_t<decltype(*std::declval<T>().begin())>;
        
        consteval static int calc_value() {
            if constexpr (container<value_type>) {
                return container_dim<value_type>::calc_value() + 1;
            } else {
                return 1;
            }
        }
    };
    
    template<container T>
    constexpr int container_dim_v = container_dim<T>::calc_value();
    
    static_assert(container_dim_v<std::vector<int>> == 1);
    static_assert(container_dim_v<std::vector<std::vector<int>>> == 2);
}

/**
 * Definitions for the to_str function.
 */
namespace ugly::detail {
    
    auto to_str_printable(const printable auto& t) -> std::string {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }
    
    auto to_str_container(const container auto& t,
                          int dim = container_dim_v<std::decay_t<decltype(t)>>) -> std::string
    {
        constexpr auto to_str_container_1d = [](const container auto& t) {
            static_assert(!container<decltype(*t.begin())>);
            
            if (t.begin() == t.end()) {
                return std::string("[]");
            }
            
            auto ret = std::string("[");
            
            int idx = 0;
            for (auto it = t.begin(); it != t.end(); ++it, ++idx) {
                auto cat = str_cat(to_str(*it), ", ");
                ret.append(std::move(cat));
            }
            ret.pop_back();
            ret.back() = ']';
            
            return ret;
        };
        
        auto to_str_container_md = [dim](const container auto& t_) {
            constexpr int dim_target = container_dim_v<std::decay_t<decltype(*t_.begin())>>;
            if (t_.begin() == t_.end()) {
                return std::string("[]");
            }
            
            auto ret = std::string("[\n");
            
            int idx = 0;
            for (auto it = t_.begin(); it != t_.end(); ++it, ++idx) {
                auto cat = str_cat(str_repetition("    ", dim - dim_target), to_str_container(*it, dim), ",\n");
                ret.append(std::move(cat));
            }
            ret.pop_back();
            ret.pop_back();
            ret.append("\n");
            ret.append(str_repetition("    ", dim - dim_target - 1));
            ret.append("]");
            
            return ret;
        };
        
        if constexpr (!container<decltype(*t.begin())>) {
            return to_str_container_1d(t);
        } else {
            return to_str_container_md(t);
        }
    }
    
    template<array T>
    auto to_str_array(const T& t) -> std::string {
        constexpr std::size_t SIZE = std::extent_v<T>;
        
        if (SIZE == 0) {
            return "[]";
        }
        
        auto ret = std::string("[");
        
        for (int i = 0; i < SIZE; ++i) {
            auto cat = str_cat(std::to_string(i), ": ", to_str(t[i]), ", ");
            ret.append(std::move(cat));
        }
        ret.pop_back();
        ret.back() = ']';
        
        return ret;
    }
    
    template<named_tuple T>
    auto to_str_named_tuple(const T& t) -> std::string {
        constexpr int SIZE = std::extent_v<decltype(T::mem_names)>;
        const auto& names = T::mem_names;
        
        std::stringstream ss;
        if constexpr (SIZE == 0) {
            return "()";
        } else if constexpr (SIZE == 1) {
            const auto& [a] = t;
            return str_cat("(", names[0], ": ", to_str(a), ")");
        } else if constexpr (SIZE == 2) {
            const auto& [a, b] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ")");
        } else if constexpr (SIZE == 3) {
            const auto& [a, b, c] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ")");
        } else if constexpr (SIZE == 4) {
            const auto& [a, b, c, d] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ")");
        } else if constexpr (SIZE == 5) {
            const auto& [a, b, c, d, e] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ")");
        } else if constexpr (SIZE == 6) {
            const auto& [a, b, c, d, e, f] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ", ",
                           names[5], ": ", to_str(f), ")");
        } else if constexpr (SIZE == 7) {
            const auto& [a, b, c, d, e, f, g] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ", ",
                           names[5], ": ", to_str(f), ", ",
                           names[6], ": ", to_str(g), ")");
        } else if constexpr (SIZE == 8) {
            const auto& [a, b, c, d, e, f, g, h] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ", ",
                           names[5], ": ", to_str(f), ", ",
                           names[6], ": ", to_str(g), ", ",
                           names[7], ": ", to_str(h), ")");
        } else if constexpr (SIZE == 9) {
            const auto& [a, b, c, d, e, f, g, h, i] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ", ",
                           names[5], ": ", to_str(f), ", ",
                           names[6], ": ", to_str(g), ", ",
                           names[7], ": ", to_str(h), ", ",
                           names[8], ": ", to_str(i), ")");
        } else if constexpr (SIZE == 10) {
            const auto& [a, b, c, d, e, f, g, h, i, j] = t;
            return str_cat("(",
                           names[0], ": ", to_str(a), ", ",
                           names[1], ": ", to_str(b), ", ",
                           names[2], ": ", to_str(c), ", ",
                           names[3], ": ", to_str(d), ", ",
                           names[4], ": ", to_str(e), ", ",
                           names[5], ": ", to_str(f), ", ",
                           names[6], ": ", to_str(g), ", ",
                           names[7], ": ", to_str(h), ", ",
                           names[8], ": ", to_str(i), ", ",
                           names[9], ": ", to_str(j), ")");
        }
        
        else {
            return str_cat("<object at ", to_str(&t), " with >10 members>");
        }
    }
    
    template<unpackable T>
    auto to_str_unpackable(const T& t) -> std::string {
        constexpr int n = T::mem_num;
        
        std::stringstream ss;
        if constexpr (n == 0) {
            return "()";
        } else if constexpr (n == 1) {
            const auto& [a] = t;
            return str_cat("(", to_str(a), ")");
        } else if constexpr (n == 2) {
            const auto& [a, b] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ")");
        } else if constexpr (n == 3) {
            const auto& [a, b, c] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ")");
        } else if constexpr (n == 4) {
            const auto& [a, b, c, d] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ")");
        } else if constexpr (n == 5) {
            const auto& [a, b, c, d, e] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ")");
        } else if constexpr (n == 6) {
            const auto& [a, b, c, d, e, f] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ", ",
                           to_str(f), ")");
        } else if constexpr (n == 7) {
            const auto& [a, b, c, d, e, f, g] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ", ",
                           to_str(f), ", ", to_str(g), ")");
        } else if constexpr (n == 8) {
            const auto& [a, b, c, d, e, f, g, h] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ", ",
                           to_str(f), ", ", to_str(g), ", ", to_str(h), ")");
        } else if constexpr (n == 9) {
            const auto& [a, b, c, d, e, f, g, h, i] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ", ",
                           to_str(f), ", ", to_str(g), ", ", to_str(h), ", ",
                           to_str(i), ")");
        } else if constexpr (n == 10) {
            const auto& [a, b, c, d, e, f, g, h, i, j] = t;
            return str_cat("(", to_str(a), ", ", to_str(b), ", ",
                           to_str(c), ", ", to_str(d), ", ", to_str(e), ", ",
                           to_str(f), ", ", to_str(g), ", ", to_str(h), ", ",
                           to_str(i), ", ", to_str(j), ")");
        }
        
        else {
            str_cat("<object at ", to_str(&t), " with >10 members>");
        }
    }
    
    auto to_str_rule_undefined(const auto& t) -> std::string {
        return str_cat("<obj ", typeid(t).name(), " @", to_str(&t), ">");
    }
    
    template<typename T>
    auto to_str(const T& t) -> std::string {
        if constexpr (basic_rule_defined<T>) {
            return to_str_basic(t);
        } else if constexpr (printable<T>) {
            return to_str_printable(t);
        } else if constexpr (container<T>) {
            return to_str_container(t);
        } else if constexpr (array<T>) {
            return to_str_array(t);
        } else if constexpr (named_tuple<T>) {
            return to_str_named_tuple(t);
        } else if constexpr (unpackable<T>) {
            return to_str_unpackable(t);
        }
        
        else {
            return to_str_rule_undefined(t);
        }
    }
}

namespace ugly::detail {
    template<typename T>
    void fmt_helper(std::string &string_template, const T& val) {
        auto pat = std::regex(R"(\{[^\}]*\})");
        auto match = std::smatch();
        if (not std::regex_search(string_template, match, pat)) {
            return;
        }
        auto policy = match.str();
        if (policy == "{}") {
            string_template =
                    match.prefix().str() + to_str(val)
                    + match.suffix().str();
        }
        
        else {
            string_template =
                    match.prefix().str() + to_str(val)
                    + match.suffix().str();
        }
    }
    
    /**
     * light fmt function.
     * @tparam Args any types for arguments
     * @param string_template template string
     * @param args arguments
     * @return formatted string
     */
    template<typename... Args>
    [[maybe_unused]]
    std::string fmt(std::string string_template, const Args&... args) {
        (fmt_helper(string_template, args), ...);
        return string_template;
    }
}

namespace ugly::detail {
    [[maybe_unused]]
    inline decltype(auto) drop(const auto& t) {
        std::cout << to_str(t);
        return t;
    }
}

namespace ugly::detail {
    class Printer {
    
    public:
        [[maybe_unused]]
        Printer& operator<<(const auto& t) {
            std::cout << ugly::detail::fmt("/{}/", t) << std::endl;
            return *this;
        }
        
        template<typename... T>
        [[maybe_unused]]
        Printer& fmtln(const std::string& s_fmt, const T&... t) {
            std::cout << ugly::detail::fmt(s_fmt, t...) << std::endl;
            return *this;
        }
        
        template<typename T>
        [[maybe_unused]]
        Printer& ln(const T& t) {
            std::cout << to_str(t) << std::endl;
            return *this;
        }
        
        [[maybe_unused]]
        decltype(auto) operator*(auto&& t) {
            std::cout << ugly::detail::to_str(t) << std::endl;
            return t;
        }
        
        [[maybe_unused]]
        decltype(auto) drop(auto&& t) {
            std::cout << ugly::detail::to_str(t) << std::endl;
            return t;
        }
    };
    
    Printer dout;
}

/**
 * Final export
 */
namespace ugly {
    using detail::to_str;
    using detail::fmt;
    using detail::dout;
    using detail::drop;
}

#endif
