#ifndef INCLUDED_SROOK_ARRAY_MAKE_ARRAY_HPP
#define INCLUDED_SROOK_ARRAY_MAKE_ARRAY_HPP
#include<array>
#include<srook/type_traits/conjunction.hpp>
#include<srook/type_traits/negation.hpp>
#include<type_traits>

namespace srook{

namespace detail{

	template<class> struct is_ref_wrapper : std::false_type {};
	template<class T> struct is_ref_wrapper<std::reference_wrapper<T>> : std::true_type {};
	
	template<class T>
	using not_ref_wrapper = srook::negation<is_ref_wrapper<std::decay_t<T>>>;

	template <class D,class...> struct return_type_helper { using type = D; };
	template <class... Ts>
	struct return_type_helper<void, Ts...> : std::common_type<Ts...>{
		static_assert(srook::conjunction_v<not_ref_wrapper<Ts>...>,"Ts cannot contain reference_wrappers when D is void");
	};
				   
	template <class D,class... Ts>
	using return_type = std::array<typename return_type_helper<D,Ts...>::type,sizeof...(Ts)>;

} // namespace detail
	 
template<class D = void,class... Ts>
SROOK_DEPRECATED constexpr detail::return_type<D, Ts...> make_array(Ts&&... t)
{
	return {std::forward<Ts>(t)... };
}

} // namespace srook

#endif
