#ifdef __cplusplus
#ifndef INCLUDED_SROOK_CONFIG_HPP
#define INCLUDED_SROOK_CONFIG_HPP
#include<srook/type_traits/enable_disable_if.hpp>

#ifdef POSSIBLE_TO_INCLUDE_STD_ENABLE_IF
#ifndef SROOK_NO_CXX11_NULLPTR
#define VARIADIC_REQUIRES(...) typename std::enable_if<static_cast<bool>((__VA_ARGS__ + ...)),std::nullptr_t>::type =nullptr
#define REQUIRES(...) typename std::enable_if<__VA_ARGS__,std::nullptr_t>::type =nullptr
#else
#define VARIADIC_REQUIRES(...) typename std::enable_if_t<static_cast<bool>((__VA_ARGS__ + ...))>::type* =0
#define REQUIRES(...) typename std::enable_if<__VA_ARGS__>::type* =0
#endif

#elif defined(POSSIBLE_TO_INCLUDE_BOOST_ENABLE_IF)
#ifndef SROOK_NO_CXX11_NULLPTR
#define VARIADIC_REQUIRES(...) typename boost::enable_if_c<static_cast<bool>((__VA_ARGS__ + ...)),std::nullptr_t>::type =nullptr
#define REQUIRES(...) typename boost::enable_if_c<__VA_ARGS__,std::nullptr_t>::type =nullptr
#else
#define VARIADIC_REQUIRES(...) typename boost::enable_if_c<static_cast<bool>((__VA_ARGS__ + ...))>::type* =0
#define REQUIRES(...) typename boost::enable_if_c<__VA_ARGS__>::type* =0
#endif

#else
#ifndef SROOK_NO_CXX11_NULLPTR
#define VARIADIC_REQUIRES(...) typename srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...))>::type =nullptr
#define REQUIRES(...) typename srook::enable_if<__VA_ARGS__>::type =nullptr
#else
#define VARIADIC_REQUIRES(...) typename srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...)),void*>::type =0
#define REQUIRES(...) typename srook::enable_if<__VA_ARGS__,void*>::type =0
#endif
#endif

#endif
#endif
