#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_PREV_PERMUTATION_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_PREV_PERMUTATION_HPP
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct prev_permutation_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return prev_permutation(r.begin(),r.end());
	}
};

template<class Compare>
struct prev_permutation_comp_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr prev_permutation_comp_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return prev_permutation(r.begin(),r.end(),std::move(comp_));
	}
private:
	Compare comp_;
};

constexpr prev_permutation_t prev_permutation()
{
	return prev_permutation_t();
}

template<class Compare>
constexpr prev_permutation_comp_t<std::decay_t<Compare>> prev_permutation(Compare&& comp)
{
	return prev_permutation_comp_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::prev_permutation;

} // namespace adaptors
} // namespace srook

#endif
