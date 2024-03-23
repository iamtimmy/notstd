#pragma once

#ifndef __has_builtin
#define __has_builtin(...) 0
#endif
#ifndef __has_attribute
#define __has_attribute(...) 0
#endif
#ifndef __has_cpp_attribute
#define __has_cpp_attribute(...) 0
#endif
#ifndef __has_feature
#define __has_feature(...) 0
#endif
#ifndef __has_include
#define __has_include(...) 0
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__AMD_64) || defined(_M_AMD64) || defined(_M_IX86) || defined(__i386)
#ifndef NOTSTD_X86_32
#if UINTPTR_MAX == 0xFFFFFFFF
#define NOTSTD_X86_32 1
#define NOTSTD_X86_64 0
#else
#define NOTSTD_X86_32 0
#define NOTSTD_X86_64 1
#endif
#endif
#else
#error "unsupported architecture"
#endif

#if defined(__GNUC__) || defined(__clang__)
#define NOTSTD_GNU 1
#else
#define NOTSTD_GNU 0
#endif
#ifdef _MSC_VER
#define NOTSTD_MS_EXTS 1
#if !NOTSTD_GNU
#define NOTSTD_MSVC 1
#endif
#endif

#ifndef NOTSTD_DEBUG
#if defined(NDEBUG) && !defined(_DEBUG)
#define NOTSTD_DEBUG 0
#else
#define NOTSTD_DEBUG 1
#endif
#endif

#if NOTSTD_MS_EXTS
#define NOTSTD_FN_NAME __FUNCSIG__
#else
#define NOTSTD_FN_NAME __PRETTY_FUNCTION__
#endif

#if NOTSTD_GNU
#define NOTSTD_INLINE           [[gnu::always_inline]]
#define NOTSTD_NOINLINE         [[gnu::noinline]]
#define NOTSTD_TRIVIAL_ABI      [[clang::trivial_abi]]
#define NOTSTD_COLD             [[gnu::cold, gnu::noinline, clang::disable_tail_calls]]
#define NOTSTD_COLD_SCOPE
#define NOTSTD_HOT              [[gnu::hot]]
#define NOTSTD_HOT_SCOPE
#define NOTSTD_CASTEXPRESSION   [[gnu::always_inline, nodiscard]]
#elif NOTSTD_MSVC
#define NOTSTD_INLINE           [[msvc::forceinline]]
#define NOTSTD_NOINLINE         [[msvc::noinline]]
#define NOTSTD_TRIVIAL_ABI
#define NOTSTD_COLD             [[msvc::noinline]]
#define NOTSTD_COLD_SCOPE       [[msvc::noinline_calls]]
#define NOTSTD_HOT
#define NOTSTD_HOT_SCOPE        [[msvc::flatten]]
#define NOTSTD_CASTEXPRESSION   [[msvc::intrinsic, nodiscard]]
#endif

#ifndef NOTSTD_STRINGIFY
#define NOTSTD_STRINGIFY(a) \
    #a
#endif

#ifndef NOTSTD_STRCAT_I
#define NOTSTD_STRCAT_I(a, b) \
    a##b
#endif

#ifndef NOTSTD_STRCAT
#define NOTSTD_STRCAT(a, b) \
    NOTSTD_STRCAT_I(a, b)
#endif