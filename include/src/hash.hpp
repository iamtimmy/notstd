#pragma once

#include "integers.hpp"

namespace notstd::hash {
    static consteval u32 cfnv1a32(const char* sig) {
        auto tmp = 0x811c9dc5u;
        while (*sig != 0) {
            tmp ^= *sig++;
            tmp *= 0x01000193;
        }
        return tmp;
    }

    static constexpr u32 fnv1a32(const char* sig) {
        auto tmp = 0x811c9dc5u;
        while (*sig != 0) {
            tmp ^= *sig++;
            tmp *= 0x01000193;
        }
        return tmp;
    }
}