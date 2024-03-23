#pragma once

#include "constexpr.hpp"

namespace notstd {
    template<class F>
    struct NOTSTD_TRIVIAL_ABI deferred {
        F fn;

        template<class T>
        NOTSTD_INLINE constexpr deferred(T&& functor) : fn(forward<T>(functor)) {}

        NOTSTD_INLINE constexpr ~deferred() { fn(); }

        deferred(deferred const&) = delete;
        deferred(deferred&&) = delete;
        deferred& operator=(deferred const&) = delete;
        deferred& operator=(deferred&&) = delete;
    };

    struct deferred_factory {
        template<class T>
        [[nodiscard]] NOTSTD_INLINE constexpr deferred<remove_reference_t<T>> operator*(T&& functor) {
            return {forward<T>(functor)};
        }
    };
}

#ifndef defer
#define defer const auto NOTSTD_STRCAT(_deferred, __COUNTER__) = ::notstd::deferred_factory{}* [&]
#endif