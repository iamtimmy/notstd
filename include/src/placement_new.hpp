#pragma once

#if defined(_KERNEL_MODE)

inline void* operator new(size_t, void* where) noexcept {
    return where;
}

inline void operator delete(void*, void*) noexcept {
    return;
}

inline void* operator new[](size_t, void* where) noexcept {
    return where;
}

inline void operator delete[](void*, void*) noexcept {
    return;
}

#endif

