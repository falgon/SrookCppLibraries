#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MAX_ELEMENT_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MAX_ELEMENT_HPP
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct max_element_t{
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
		std::max_element(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct max_element_compare_t{
	template<REQUIRES(srook::is_callable_v<Compare>)>
	explicit constexpr max_element_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
		std::max_element(r.cbegin(),r.cend(),std::move(comp_));
	}
private:
	Compare comp_;
};

constexpr max_element_t max_element()
{
	return max_element_t();
}
template<class Compare>
constexpr max_element_compare_t<std::decay_t<Compare>> max_element(Compare&& comp)
{
	return max_element_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline nmaespace v1
} // namesapce detail

using detail::max_element;

} // namesapce adaptors
} // namesapce srook

#endif
