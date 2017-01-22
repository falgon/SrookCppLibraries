#ifndef INCLUDED_SROOK_ADAPTOR_FILL
#define INCLUDED_SROOK_ADAPTOR_FILL
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/fill.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL
#include<boost/range/algorithm/fill.hpp>
#else
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct fill_t{
	explicit constexpr fill_t(const T& t):data_(t){}
	explicit constexpr fill_t(T&& t):data_(std::move(t)){}
	
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator> operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL
		boost::fill(r,std::move(data_));
#else
		std::fill(r.begin(),r.end(),std::move(data_));
#endif
		return srook::make_range_iterator(r.cbegin(),r.cend());
	}
private:
	T data_;
};
template<class T>
constexpr fill_t<std::decay_t<T>> fill(T&& t)
{
	return fill_t<std::decay_t<T>>(std::forward<T>(t));
}

} // inline namespace v1
} // namespace detail

using detail::fill;

} // namespace adaptors
} // namespace srok

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL
#endif

#endif
