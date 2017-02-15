#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_COUNT
#define INCLUDED_SROOK_RANGE_ADAPTOR_COUNT
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<iterator>
#include<algorithm>
#include<type_traits>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct count_t{
	explicit constexpr count_t(T t):value(std::move(t)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::iterator_traits<typename std::decay_t<Range>::iterator>::difference_type operator()(Range&& r)
	{
		return std::count(r.cbegin(),r.cend(),std::move(value));
	}
private:
	T value;
};
template<class T>
constexpr count_t<std::decay_t<T>> count(T&& t)
{
	return count_t<std::decay_t<T>>(std::forward<T>(t));
}

} // inline namespace
} // namespace detail

using detail::count;

} // namespace adaptors
} // namespace srook
#endif
