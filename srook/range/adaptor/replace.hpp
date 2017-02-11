#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/replace.hpp>)
#include<boost/range/algorithm/replace.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_ALGORITHM_REPLACE
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct replace_t{
	explicit constexpr replace_t(const T& old_value,const T& new_value):old_value_(old_value),new_value_(new_value){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::decay_t<Range>& operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_ALGORITHM_REPLACE
		boost::range::replace(std::forward<Range>(r),old_value_,new_value_);
#else
		std::replace(r.begin(),r.end(),old_value_,new_value_);
#endif
		return r;
	}
private:
	const T& old_value_;
	const T& new_value_;
};

template<class T>
constexpr replace_t<std::decay_t<T>> replace(T&& old_,T&& new_)
{
	return replace_t<std::decay_t<T>>(std::forward<T>(old_),std::forward<T>(new_));
}

} // inline namespace v1
} // namespace detail

using detail::replace;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_ALGORITHM_REPLACE
#undef POSSIBLE_TO_INCLUDE_BOOST_ALGORITHM_REPLACE
#endif
#endif
