#ifndef INCLUDED_SROOK_NEXT_PERMUTATION_HPP
#define INCLUDED_SROOK_NEXT_PERMUTATION_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct next_permutation_t{
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return
		std::next_permutation(r.begin(),r.end());
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
		std::next_permutation(r.begin(),r.end(),std::move(comp_));
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

} // namesapce adaptors
} // namespace srook

#endif
