// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#include<type_traits>

namespace srook{

	template<class...>
	struct conjunction:std::true_type{};
	
	template<class B1>
	struct conjunction<B1>:B1{};
	
	template<class B1,class... Bn>
	struct conjunction<B1,Bn...>:std::conditional_t<bool(B1::value),conjunction<Bn...>,B1>{};

	template<class... B>
#if __cplusplus >= 201703L
	inline 
#endif
	constexpr bool conjunction_v = conjunction<B...>::value;

} // namespace srook
#endif
