#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_COUNT
#define INCLUDED_SROOK_RANGE_ADAPTOR_COUNT
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/count.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_COUNT
#include<boost/range/algorithm/count.hpp>
#else
#include<iterator>
#include<algorithm>
#include<type_traits>
#endif

namespace srook{
namespace adaptors{
inline namespace v1{

template<class T>
struct count_t{
	explicit constexpr count_t(T t):value(std::move(t)){}
	template<class Range>
	typename std::iterator_traits<typename std::decay_t<Range>::iterator>::difference_type operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_COUNT
		return boost::range::count(std::forward<Range>(r),std::move(value));
#else
		return std::count(r.cbegin(),r.cend(),std::move(value));
#endif
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
} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_COUNT
#undef POSSIBLE_TO_BOOST_RANGE_COUNT
#endif
#endif
