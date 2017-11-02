#ifndef INCLUDED_SROOK_UTILITY_DETAIL_NON_SUPPORT_MOVE_SEMANTICS_HPP
#define INCLUDED_SROOK_UTILITY_DETAIL_NON_SUPPORT_MOVE_SEMANTICS_HPP
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/noexcept_detection.hpp>

#define DEPEMES	SROOK_DEPRECATED_MESSAGE(\
			"\nThe move semantics is only supported since C++11.\n"\
			"You can continue to use this function; however, it will do nothing."\
	)

#define DEF_MOVE_SEMANTICS_UTILITIES(FuncName)\
	template <class T>\
	DEPEMES\
	T& FuncName(T& t) SROOK_NOEXCEPT_TRUE\
	{\
		return t;\
	}
#endif
