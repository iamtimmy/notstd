#pragma once

#include "macros.hpp"

namespace notstd {
    template<class T, T v>
    struct integral_constant
    {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant; // using injected-class-name
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; } // since c++14
    };

    template< bool B >
    using bool_constant = integral_constant<bool, B>;

    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    template<class T, class U>
    struct is_same : false_type {};

    template<class T>
    struct is_same<T, T> : true_type {};

    template< class T, class U >
    inline constexpr bool is_same_v = is_same<T, U>::value;

    template<class T>
    struct remove_reference { using type = T; };

    template<class T>
    struct remove_reference<T&> { using type = T; };

    template<class T>
    struct remove_reference<T&&> { using type = T; };

    template<class T>
    using remove_reference_t = typename remove_reference<T>::type;

    template<class T>
    struct remove_cv { using type = T; };
    template<class T>
    struct remove_cv<const T> { using type = T; };
    template<class T>
    struct remove_cv<volatile T> { using type = T; };
    template<class T>
    struct remove_cv<const volatile T> { using type = T; };

    template<class T>
    struct remove_const { using type = T; };
    template<class T>
    struct remove_const<const T> { using type = T; };

    template<class T>
    struct remove_volatile { using type = T; };
    template<class T>
    struct remove_volatile<volatile T> { using type = T; };

    template<class T>
    using remove_cv_t = typename remove_cv<T>::type;
    template<class T>
    using remove_const_t = typename remove_const<T>::type;
    template<class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template<class T>
    struct remove_cvref { using type = remove_cv_t<remove_reference_t<T>>; };

    template<class T>
    using remove_cvref_t = typename remove_cvref<T>::type;

    template <class>
    inline constexpr bool is_lvalue_reference_v = false; // determine whether type argument is an lvalue reference

    template <class T>
    inline constexpr bool is_lvalue_reference_v<T&> = true;

    template <class T>
    struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>> {};

    template<class T>
    NOTSTD_CASTEXPRESSION constexpr T&& forward(remove_reference_t<T>&& param) noexcept {
        static_assert(!is_lvalue_reference_v<T>, "bad forward call");
        return static_cast<T&&>(param);
    }

    template<class T>
    NOTSTD_CASTEXPRESSION constexpr T&& forward(remove_reference_t<T>& param) noexcept {
        return static_cast<T&&>(param);
    }
}