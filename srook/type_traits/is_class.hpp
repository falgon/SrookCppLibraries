// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#if !__has_include(<type_traits>)
#include<srook/config/nullptr.hpp>
#endif
namespace srook{
	namespace detail{
		template<class T>
		char test(int T::*);
		struct two{
			char c[2];
		};
		template<class T>
		two test(...);
	}

	template<class T>
	struct is_class{
		enum{value=sizeof(detail::test<T>(0))==1};
	};
#if !__has_include(<type_traits>)
	template<>
	struct is_class<srook::nullptr_t>:std::false_type{};
#endif
}
#endif
