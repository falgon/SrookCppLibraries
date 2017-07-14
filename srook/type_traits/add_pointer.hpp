// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_ADD_POINTER_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_ADD_POINTER_HPP
#include<srook/config/compiler.hpp>
namespace srook{

template<class T>
struct add_pointer{
	typedef T* type;
};

} // namespace srook
#endif
