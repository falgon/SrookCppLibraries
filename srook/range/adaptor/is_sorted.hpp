#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_IS_SORTED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_IS_SORTED_HPP
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct is_sorted_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return
		std::is_sorted(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct is_sorted_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_sorted_compare_t(const Compare& comp):comp_(comp){}
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_sorted_compare_t(Compare&& comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return 
		std::is_sorted(r.cbegin(),r.cend(),std::move(comp_));
	}
private:
	Compare comp_;
};

constexpr is_sorted_t is_sorted()
{
	return is_sorted_t();
}

template<class Compare>
constexpr is_sorted_compare_t<std::decay_t<Compare>> is_sorted(Compare&& comp)
{
	return is_sorted_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::is_sorted;

} // namespace adaptors
} // namespace srook

#endif
