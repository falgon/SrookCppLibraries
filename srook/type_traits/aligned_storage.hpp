// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t L_>
struct aligned_storage_impl {
	union type_ {
		unsigned char data_[L_];
		struct SROOK_ATTRIBUTE_ALIGNED {} al_;
	};
};

} // namespace detail

template <std::size_t L_
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
, std::size_t Al_ = SROOK_ALIGN_OF(typename detail::aligned_storage_impl<L_>::type_)
#endif
>
struct aligned_storage {
	union type {
		unsigned char data_[L_];
		struct
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
		SROOK_ATTRIBUTE_ALIGNED_X(Al_)
#else
		SROOK_ATTRIBUTE_ALIGNED_X(SROOK_ALIGN_OF(typename detail::aligned_storage_impl<L_>::type_))
#endif
		{} al_;
	};
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::aligned_storage;

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t L, std::size_t Al = SROOK_ALIGN_OF(typename type_traits::detail::aligned_storage_impl<L>::type_)>
using aligned_storage_t = typename aligned_storage<L, Al>::type;
#endif

} // namespace srook
#endif
