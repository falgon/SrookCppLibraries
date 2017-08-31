#ifndef INCLUDED_SROOK_CONFIG_DEPRECATED_CPP_LIB_STD_ITERATOR_HPP
#define INCLUDED_SROOK_CONFIG_DEPRECATED_CPP_LIB_STD_ITERATOR_HPP

#include<srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include<srook/config/cpp_predefined/macro_names.hpp>
#include<iterator>

#if SROOK_CPLUSPLUS <= SROOK_CPLUSPLUS14_CONSTANT
#	define SROOK_STD_ITERATOR_DEPRECATED 0
#	define SROOK_STD_ITERATOR(ITERATOR_CATEGORY,T,DISTANCE,POINTER,REFERENCE) std::iterator<ITERATOR_CATEGORY,T,DISTANCE,POINTER,REFERENCE>
#else
#	define SROOK_STD_ITERATOR_DEPRECATED 1

namespace srook{
namespace iterator{
namespace when_the_std_iterator_was_deprecated_empty_base{

template<class,class,class,class,class> 
class X{
	void* operator new(std::size_t) = delete;
	void* operator new[](std::size_t) = delete;
	void operator delete(void*,std::size_t)  = delete;
	void operator delete[](void*,std::size_t) = delete;
};

} // when_the_std_iterator_was_deprecated_empty_base
} // iterator
} // namespace srook


#	define SROOK_STD_ITERATOR(ITERATOR_CATEGORY,T,DISTANCE,POINTER,REFERENCE) srook::iterator::when_the_std_iterator_was_deprecated_empty_base::X<ITERATOR_CATEGORY,T,DISTANCE,POINTER,REFERENCE>
#endif

#endif
