// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_DETECTOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_DETECTOR_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/feature.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class Default, class Alwaysvoid, template <class...> class Op, class... Args>
struct detector {
    typedef SROOK_FALSE_TYPE value_t;
    typedef Default type;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, SROOK_DEDUCED_TYPENAME voider<Op<Args...> >::type, Op, Args...> {
    typedef SROOK_TRUE_TYPE value_t;
    typedef Op<Args...> type;
};

template <class Default, template <class...> class Op, class... Args>
using detector_or = detector<Default, void, Op, Args...>;

template <class Default, template <class...> class Op, class... Args>
using detector_or_t = SROOK_DEDUCED_TYPENAME detector_or<Default, Op, Args...>::type;


} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits
} // namespace srook

#endif
#endif
