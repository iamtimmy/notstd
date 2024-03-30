#pragma once

#include "macros.hpp"
#include "integers.hpp"
#include "hash.hpp"
#include "constexpr.hpp"
#include "placement_new.hpp"
#include "defer.hpp"

namespace notstd {
    NOTSTD_INLINE static inline void breakpoint() {
#if __has_builtin(__builtin_debugtrap)
        __builtin_debugtrap();
#else
        __debugbreak();
#endif
    }

    NOTSTD_INLINE static inline void assume_that(bool condition) {
#if __has_builtin(__builtin_assume)
        __builtin_assume( condition );
#else
        __assume( condition );
#endif
    }

    NOTSTD_INLINE [[noreturn]] static inline void assume_unreachable() {
#if __has_builtin(__builtin_unreachable)
        __builtin_unreachable();
#else
        assume_that(false);
#endif
    }

    template<typename T>
    NOTSTD_INLINE decltype(auto) value_as(auto&& v){
        return (T)v;
    }
}