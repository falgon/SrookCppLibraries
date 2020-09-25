// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CALLABLE
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CALLABLE
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct is_callable_impl {
private:
    typedef char (&yes)[1];
    typedef char (&no)[2];

    struct Fallback {
        void operator()();
    };
    struct derived : T, Fallback {
    };

    template <class U, U>
    struct Check;

    template <class>
    static yes test(...);
    template <class C>
    static no test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static SROOK_CONSTEXPR_OR_CONST bool value = sizeof(test<derived>(nullptr)) == sizeof(yes);
};

template <class T>
struct is_callable : std::conditional<std::is_class<T>::value, is_callable_impl<T>, SROOK_FALSE_TYPE>::type {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::is_callable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
constexpr bool is_callable_v = type_traits::detail::is_callable<T>::value;
#endif

} // namespace srook

#endif
