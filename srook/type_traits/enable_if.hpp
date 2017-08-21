// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ENABLE_IF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>

namespace srook {

template <bool, class>
struct enable_if;

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class T>
using enable_if_t = typename enable_if<b, T>::type;
#endif

} // namespace srook

#endif
