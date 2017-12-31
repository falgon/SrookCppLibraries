// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DETECTED_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DETECTED_HPP

#include <srook/type_traits/detail/detector.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/utility/enable_copy_move.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

struct nonesuch : disable_special_functions<nonesuch> {};

template <template <class...> class Op, class... Args>
using is_detected = SROOK_DEDUCED_TYPENAME detail::detector<nonesuch, void, Op, Args...>::value_t;

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class Op, class... Args>
using detected_t = SROOK_DEDUCED_TYPENAME type_traits::detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template <class...> class Op, class... Args>
using detected_or = type_traits::detail::detector_or<Default, Op, Args...>;

template <class Default, template <class...> class Op, class... Args>
using detected_or_t = SROOK_DEDUCED_TYPENAME detected_or<Default, Op, Args...>::type;

template <class Expected, template <class...> class Op, class... Args>
using is_detected_exact = is_same<Expected, detected_t<Op, Args...>>;

template <class To, template <class...> class Op, class... Args>
using is_detected_convertible = is_convertible<detected_t<Op, Args...>, To>;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::nonesuch;
using type_traits::is_detected;

#if SROOK_CPP_ALIAS_TEMPLATES
using type_traits::detected_t;
using type_traits::detected_or;
using type_traits::detected_or_t;
using type_traits::is_detected_exact;
using type_traits::is_detected_convertible;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <template <class...> class Op, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_detected_v = is_detected<Op, Args...>::value;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class Expected, template<class...> class Op, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

template <class To, template <class...> class Op, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;
#endif
#endif

} // namespace srook

#endif
#endif
