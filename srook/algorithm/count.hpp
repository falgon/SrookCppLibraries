#ifndef INCLUDED_SROOK_ALGORITHM_COUNT_HPP
#define INCLUDED_SROOK_ALGORITHM_COUNT_HPP
#include<srook/tuple/tuple_filter_type.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<algorithm>

namespace srook{

namespace detail{

struct Apply_Counter{
	struct invoker{
		template<class... Ts,class Target,std::size_t index,class... Args>
		static std::size_t 
		apply(const std::tuple<Ts...>&,Target&&,std::integral_constant<std::size_t,index>,std::size_t counter,Args&&...)
		{
			return counter;
		}
	};

	struct unpacker{
		template<class... Ts,class Target,std::size_t index,class... Args>
		static std::size_t
		apply(const std::tuple<Ts...>& tpl,Target&& t,std::integral_constant<std::size_t,index>,std::size_t counter,Args&&... args)
		{
			if(std::get<index>(tpl)==t){
				return Apply_Counter::apply(tpl,std::forward<Target>(t),std::integral_constant<std::size_t,index-1>(),counter+1,std::get<index>(tpl),std::forward<Args>(args)...);
			}else{
				return Apply_Counter::apply(tpl,std::forward<Target>(t),std::integral_constant<std::size_t,index-1>(),counter,std::get<index>(tpl),std::forward<Args>(args)...);
			}
		}
	};

	template<class... Ts,class Target,std::size_t index,class... Args>
	static std::size_t apply(const std::tuple<Ts...>& tpl,Target&& t,std::integral_constant<std::size_t,index> ic,std::size_t counter,Args&&... args)
	{
		return std::conditional_t<std::tuple_size<std::tuple<Ts...>>::value==sizeof...(args),invoker,unpacker>::apply(tpl,std::forward<Target>(t),std::move(ic),std::move(counter),std::forward<Args>(args)...);
	}
};

template<class Target_T>
struct counter{
	template<class T>
	using is_same=std::is_same<Target_T,T>;

	template<class... Ts,class Target>
	static std::size_t count_impl(const std::tuple<Ts...>& tpl,Target&& t)
	{
		return 
			Apply_Counter::apply(
					tuple_filter_type<is_same>(tpl),
					std::forward<Target>(t),
					std::integral_constant<std::size_t,std::tuple_size<decltype(tuple_filter_type<is_same>(tpl))>::value-1>(),0
			);
	}
};

}// namespace detail

template<class... Ts,class Target>
std::size_t count(const std::tuple<Ts...>& tp,Target&& t)
{
	return detail::counter<std::decay_t<Target>>::count_impl(tp,std::forward<Target>(t));
}

template<class Range,class Target,REQUIRES(has_iterator_v<std::decay_t<Range>>)>
std::size_t count(Range&& r,Target&& target)
{
	return std::count(std::begin(r),std::end(r),std::forward<Target>(target));
}

template<class Iter,class Target,REQUIRES(!has_iterator_v<std::decay_t<Iter>>)>
std::size_t count(Iter&& first,Iter&& last,Target&& target)
{
	return std::count(std::forward<Iter>(first),std::forward<Iter>(last),std::forward<Target>(target));
}

} // namespace srook

#endif
