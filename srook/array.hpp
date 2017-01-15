#ifndef INCLUDED_SROOOK_ARRAY
#define INCLUDED_SROOOK_ARRAY
#include<array>
#include<srook/mpl/variadic_player.hpp>

namespace srook{
inline namespace v1{

template<class... T>
constexpr auto make_array(T&&... args)noexcept -> std::array<srook::mpl::First_t<T...>,sizeof...(args)>
{
	return std::array<srook::mpl::First_t<T...>,sizeof...(args)>{{std::forward<T>(args)...}};
}

}
}

#endif
