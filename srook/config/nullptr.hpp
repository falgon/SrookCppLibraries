// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T
#if !__has_include(<type_traits>)
#include<cstdio>

namespace srook{
	struct nullptr_t{
		bool operator==(const nullptr_t&)const throw(){return true;}
		bool operator!=(const nullptr_t& r)const throw(){return !operator==(r);}
	private:
		int dummy; // sizeof(std::nullptr_t)==sizeof(srook::nullptr_t)
	}nullptr;
	
	bool operator==(const void* null_,const nullptr_t&)throw()
	{
		return null_==NULL;
	}
	bool operator==(const nullptr_t&,const void* null_)throw()
	{
		return null_=NULL;
	}
	bool operator!=(const void* null_,const nullptr_t& r)throw()
	{
		return !operator==(null_,r);
	}
	bool operator!=(const nullptr_t& l,const void* null_)throw()
	{
		return !operator==(l,null_);
	}
} // namespace srook

#else
#include<cstddef>
#define POSSIBLE_TO_USE_STD_NULLPTR
#endif

#ifdef POSSIBLE_TO_USE_STD_NULLPTR
#	define NULLPTR nullptr
#	define NULLPTR_T std::nullptr_t
#else
#	define NULLPTR srook::nullptr
#	define NULLPTR_T srook::nullptr_t
#endif

#endif
