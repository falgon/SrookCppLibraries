// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include <srook/config/feature.hpp>
#include <srook/type_traits/integral_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct alignment_of : public integral_constant<std::size_t, SROOK_ALIGN_OF(T)> {};

SROOK_INLINE_NAMESPACE_END
} // type_traits
} // srook

#endif
