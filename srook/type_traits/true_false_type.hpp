// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_TRUE_FALSE_TYPE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_TRUE_FALSE_TYPE_HPP

#if (__has_include(<type_traits>) || (__cplusplus > 201103L))
#	include<type_traits>
#	define SROOK_TRUE_TYPE std::true_type
#	define SROOK_FALSE_TYPE std::false_type
#elif __has_include(<boost/type_traits.hpp>)
#include<boost/type_traits.hpp>
#	define SROOK_TRUE_TYPE boost::true_type
#	define SROOK_FALSE_TYPE boost::false_type
#else

namespace srook{

struct true_type{
	enum{value=true};
};

struct false_type{
	enum{value=false};
};

} // namespace srook


#	define SROOK_TRUE_TYPE srook::true_type
#	define SROOK_FALSE_TYPE srook::false_type

#endif
