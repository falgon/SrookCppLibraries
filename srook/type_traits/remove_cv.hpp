// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TARITS_REMOVE_CV_HPP
#define INCLUDED_SROOK_TYPE_TARITS_REMOVE_CV_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/remove_const.hpp>
#include <srook/type_traits/remove_volatile.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct remove_cv {
	typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_cv;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using remove_cv_t = typename remove_cv<T>::type;
#endif
} // namespace srook

#endif
