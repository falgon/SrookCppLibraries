#ifndef INCLUDED_SROOK_ADAPTOR_EQUAL_RANGE
#define INCLUDED_SROOK_ADAPTOR_EQUAL_RANGE
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<map>
#include<utility>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct equal_range_range_t{
	explicit constexpr equal_range_range_t(T t):value(std::move(t)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::iterator,typename std::decay_t<R>::iterator> operator()(R&& r)
	{
		return std::equal_range(r.begin(),r.end(),std::move(value));
	}
	template<class Key,class Tp>
	auto operator()(const std::map<Key,Tp>& m)
	{
		return m.equal_range(std::move(value));
	}
private:
	T value;
};

template<class T,class Compare>
struct equal_range_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr equal_range_compare_t(T t,Compare compare):value(std::move(t)),comp(std::move(compare)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::iterator,typename std::decay_t<R>::iterator> operator()(R&& r)
	{
		return std::equal_range(r.begin(),r.end(),std::move(value),std::move(comp));
	}
private:
	T value;
	Compare comp;
};

template<class T>
constexpr equal_range_range_t<std::decay_t<T>> equal_range(T&& value)
{
	return equal_range_range_t<std::decay_t<T>>(std::forward<T>(value));
}

template<class T,class Compare>
struct equal_range_compare_t<std::decay_t<T>,std::decay_t<Compare>> equal_range(T&& value,Compare&& comp)
{
	return equal_range_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(value),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::equal_range;

} // namespace adaptors
} // namespace srook

#endif
