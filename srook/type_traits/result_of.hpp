// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#if __cplusplus >= 201103L
#include<utility>

namespace srook{
namespace detail{

template<class F,class... Args>
inline auto INVOKE(F&& f,Args&&... args)
-> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
	return std::forward<F>(f)(std::forward<Args>(args)...);
}

template<class Base,class T,class Derived>
inline auto INVOKE(T Base::*pmd,Derived&& ref)
-> decltype(std::forward<Derived>(ref).*pmd)
{
	return std::forward<Derived>(ref).*pmd;
}

template<class Base,class T,class Derived,class... Args>
inline auto INVOKE(T Base::*pmf,Derived&& ref,Args&&... args)
-> decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))
{
	return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
}

template<class PMD,class Pointer>
inline auto INVOKE(PMD&& pmd,Pointer&& ptr)
-> decltype((*std::forward<Pointer>(ptr)).*std::forward<PMD>(pmd))
{
	return (*std::forward<Pointer>(ptr)).*std::forward<PMD>(pmd);
}

template<class PMF,class Pointer,class... Args>
inline auto INVOKE(PMF&& pmf,Pointer&& ptr,Args&&... args)
-> decltype(((*std::forward<Pointer>(ptr)).*std::forward<PMF>(pmf))(std::forward<Args>(args)...))
{
	return ((*std::forward<Pointer>(ptr)).*std::forward<PMF>(pmf))(std::forward<Args>(args)...);
}

} // namespace detail
#if __cplusplus >= 201103L and __cplusplus < 201402L

template<class>
struct resulf_of;

template<class F,class... Param>
struct resulf_of<F(Param...)>{
	using type=decltype(detail::INVOKE(std::declval<F>(),std::declval<Param>()...));
};

#elif __cplusplus <= 201402L

namespace detail{

template<typename Void,typename,typename...>
struct invoke_result{};

template<typename F,typename... Args>
struct invoke_result<decltype(void(detail::INVOKE(std::declval<F>(),std::declval<Args>()...))),F,Args...>{
	using type=decltype(detail::INVOKE(std::declval<F>(),std::declval<Args>()...));
};

} // namespace detail

template<class>
struct 
#	if __cplusplus <= 201703L
[[deprecated]]
#endif
result_of;


template<class F,class... Param>
struct
#	if __cplusplus == 201703L
[[deprecated]]
#endif
result_of<F(Param...)>:detail::invoke_result<void,F,Param...>{};

template<class F,class... Param>
[[deprecated]]
using result_of_t
#	if __cplusplus == 201703L
[[deprecated]]
#	endif
=typename result_of<F,Param...>::type;

#	if  __cplusplus == 201703L

template<class F,class... Param>
struct invoke_result:detail::invoke_result<void,F,Param...>{};

template<class F,class... Param>
using invoke_result_t=typename invoke_result<F,Param...>::type;

#	endif

#endif
} // namespace srook

#endif
#endif
