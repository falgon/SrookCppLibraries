#ifndef INCLUDED_SROOK_TYPE_TRIATS_CONDITIONAL_HPP
#define INCLUDED_SROOK_TYPE_TRIATS_CONDITIONAL_HPP

#if (__has_include(<type_traits>) || (__cplusplus == 201103L))
#	include<type_traits>
#	define CONDITIONAL(x,L,R) typename std::conditional<x,L,R>::type
#	define POSSSIBLE_TO_INCLUDE_STD_TYPE_TRAITS
#elif (__has_include<boost/mpl/if.hpp>)
#	include<boost/mpl/if.hpp>
#	define CONDITIONAL(x,L,R) typename boost::mpl::if_c<x,L,R>::type
#else

namespace srook{

#if __cplusplus > 201103L
inline namespace v1{ // never active
#endif
template<bool,class,class R>
struct conditional{
	typedef R type;
};

template<class L,class R>
struct conditional<true,L,R>{
	typedef L type;
};

#if __cplusplus > 201103L

template<bool b,class L,class R>
using conditional_t=typename conditional<b,L,R>::type;

} // inline namespace 
#endif

} // namespace srook

#define CONDITIONAL(x,L,R) typename srook::conditional<x,L,R>::type

#endif
#endif
