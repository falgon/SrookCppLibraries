#ifndef INCLUDED_SROOK_NEXT_PERMUTATION_HPP
#define INCLUDED_SROOK_NEXT_PERMUTATION_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/permutation.hpp>)
#include<boost/range/algorithm/permutation.hpp>
#define POSSIBLE_TO_RANGE_INCLUDE_PERMUTATION
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct next_permutation_t{
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_RANGE_INCLUDE_PERMUTATION
		boost::range::next_permutation(std::forward<R>(r));
#else
		std::next_permutation(r.begin(),r.end());
#endif
	}
};

template<class Compare>
struct next_permutation_compare_t{
	template<REQUIRES(srook::is_callable_v<std::decay_t<Compare>>)>
	explicit constexpr next_permutation_compare_t(Compare comp):comp_(std::move(comp)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_RANGE_INCLUDE_PERMUTATION
		boost::range::next_permutation(std::forward<R>(r),std::move(comp_));
#else
		std::next_permutation(r.begin(),r.end(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

constexpr next_permutation_t next_permutation()
{
	return next_permutation_t();
}

template<class Compare>
constexpr next_permutation_compare_t<std::decay_t<Compare>> next_permutation(Compare&& comp)
{
	return next_permutation_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::next_permutation;

} // namesapce pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_RANGE_INCLUDE_PERMUTATION
#undef POSSIBLE_TO_RANGE_INCLUDE_PERMUTATION
#endif
#endif
