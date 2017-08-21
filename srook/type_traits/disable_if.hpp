// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DISABLE_IF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DISABLE_IF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>

namespace srook {

template <bool, class>
struct disable_if;

template <class T>
struct disable_if<false, T> {
    typedef T type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class T>
using disable_if_t = typename disable_if<b, T>::type;
#endif

} // namespace srook

#endif
