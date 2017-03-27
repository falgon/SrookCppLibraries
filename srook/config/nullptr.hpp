#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T
#if !__has_include(<type_traits>)
namespace srook{
	struct nullptr_t{
		bool operator==(const nullptr_t&)const noexcept{return true;}
		bool operator!=(const nullptr_t& r)const noexcept{return !operator==(*this,r);}
	}nullptr;
	
	bool operator==(const void* null_,const nullptr_t&)noexcept
	{
		return null_==NULL;
	}
	bool operator==(const nullptr_t&,const void* null_)noexcept
	{
		return null_=NULL;
	}
	bool operator!=(const void* null_,const nullptr_t& r)noexcept
	{
		return !operator==(null_,r);
	}
	bool operator!=(const nullptr_t& l,const void* null_)noexcept
	{
		return !operator==(l,null_);
	}
} // namespace srook
#else
#include<cstddef>
#define POSSIBLE_TO_USE_STD_NULLPTR
#endif
#endif
