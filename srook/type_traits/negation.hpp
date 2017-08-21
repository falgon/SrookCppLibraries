// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_NEGATION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_NEGATION_HPP
#include <type_traits>

namespace srook {

template <class B>
struct negation : std::bool_constant<!bool(B::value)> {
};

} // namespace srook

#endif
