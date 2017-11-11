// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ALIGNED_UNION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ALIGNED_UNION_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/feature.hpp>
#include <srook/type_traits/aligned_storage.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {
template <class... Ts>
struct strictest_alignment {
	static const std::size_t al_ = 0;
	static const std::size_t s_ = 0;
};

template <class T, class... Ts>
struct strictest_alignment<T, Ts...> {
	static const std::size_t al_ = SROOK_ALIGN_OF(T) > strictest_alignment<Ts...>::al_ ? SROOK_ALIGN_OF(T) : strictest_alignment<Ts...>::al_;
	static const std::size_t s_ = sizeof(T) > strictest_alignment<Ts...>::s_ ? sizeof(T) : strictest_alignment<Ts...>::s_;
};

} // namespace detail

template <std::size_t L, class... Ts>
struct aligned_union {
private:
	SROOK_STATIC_ASSERT((sizeof...(Ts) != 0), "At least one type is required");

	typedef detail::strictest_alignment<Ts...> strictype;
	static const std::size_t s_ = L > strictype::s_ ? L : strictype::s_;
public:
	static const std::size_t alignment_value = strictype::al_;
	typedef typename aligned_storage<L, alignment_value>::type type;
};

template <std::size_t L, class... Ts>
const std::size_t aligned_union<L, Ts...>::alignment_value;

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits
} // namespace srook

#endif
#endif
