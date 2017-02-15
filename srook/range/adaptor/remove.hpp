#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_HPP
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct remove_t{
	explicit constexpr remove_t(const T& t):value_(t){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::iterator operator()(Range&& r)
	{
		return std::remove(r.begin(),r.end(),std::move(value_));
	}
private:
	T value_;
};

template<class T>
constexpr remove_t<std::decay_t<T>> remove(T&& value){return remove_t<std::decay_t<T>>(std::forward<T>(value));}

} // inline namespace v1
} // namespace detail

using detail::remove;

} // namespace adaptors
} // namespace srook
#endif
