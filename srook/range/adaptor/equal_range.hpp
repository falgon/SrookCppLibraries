#ifndef INCLUDED_SROOK_ADAPTOR_EQUAL_RANGE
#define INCLUDED_SROOK_ADAPTOR_EQUAL_RANGE
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<map>
#include<utility>
#if __has_include(<boost/range/algorithm/equal_range.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL_RANGE
#include<boost/range/algorithm/equal_range.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
inline namespace v1{

template<class T>
struct equal_range_t{
	explicit constexpr equal_range_t(T t):value(std::move(t)){}

	template<class R>
	std::pair<typename std::decay_t<R>::iterator,typename std::decay_t<R>::iterator> operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL_RANGE
		return boost::range::equal_range(std::forward<R>(r),std::move(value));
#else
		return std::equal_range(r.cbegin(),r.cend(),std::move(value));
#endif
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
	explicit constexpr equal_range_compare_t(T t,Compare compare):value(std::move(t)),comp(std::move(compare)){}

	template<class R>
	std::pair<typename std::decay_t<R>::iterator,typename std::decay_t<R>::iterator> operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL_RANGE
		return boost::range::equal_range(std::forward<R>(r),std::move(value),std::move(comp));
#else
		return std::equal_range(r.cbegin(),r.cend(),std::move(value),std::move(comp));
#endif
	}
private:
	T value;
	Compare comp;
};

template<class T>
constexpr equal_range_t<std::decay_t<T>> equal_range(T&& value)
{
	return equal_range_t<std::decay_t<T>>(std::forward<T>(value));
}

template<class T,class Compare>
struct equal_range_compare_t<std::decay_t<T>,std::decay_t<Compare>> equal_range(T&& value,Compare&& comp)
{
	return equal_range_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(value),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL_RANGE
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL_RANGE
#endif

#endif
