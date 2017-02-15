#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_LEXICOGRAPHICAL_COMPARE
#define INCLUDED_SROOK_RANGE_ADAPTOR_LEXICOGRAPHICAL_COMPARE
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/adaptor/lexicographical_compare.hpp>)
#include<boost/range/adaptor/lexicographical_compare.hpp>
#define POSSIBLE_TO_RANGE_ADAPTOR_LEXICOGRAPHICAL_COMPARE
#endif
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Range>
struct lexicographical_compare_range{
	template<REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	explicit constexpr lexicographical_compare_range(const Range& r):r_(r){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return 
		std::lexicographical_compare(r.cbegin(),r.cend(),r_.cbegin(),r_.cend());
	}
private:
	const Range& r_;
};

template<class Iterator>
struct lexicographical_compare_iterator{
	template<REQUIRES(!has_iterator_v<std::decay_t<Iterator>> || is_range_iterator_v<std::decay_t<Iterator>>)>
   	explicit constexpr lexicographical_compare_iterator(Iterator first,Iterator last)
		:first_(std::move(first)),last_(std::move(last)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::lexicographical_compare(r.cbegin(),r.cend(),std::move(first_),std::move(last_));
	}
private:
	Iterator first_,last_;
};

template<class Range,class Comp>
struct lexicographical_compare_range_comp{
	template<REQUIRES( (has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<Comp> )>
	explicit constexpr lexicographical_compare_range_comp(const Range& r,Comp comp)
		:r_(r),comp_(std::move(comp)){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return
		std::lexicographical_compare(r.cbegin(),r.cend(),r_.cbegin(),r_.cend(),std::move(comp_));
	}
private:
	const Range& r_;
	Comp comp_;
};

template<class Iterator,class Comp>
struct lexicographical_compare_iterator_comp{
	template<REQUIRES( (!has_iterator_v<std::decay_t<Iterator>> || is_range_iterator_v<std::decay_t<Iterator>>) && is_callable_v<Comp> )>
	explicit constexpr lexicographical_compare_iterator_comp(Iterator first,Iterator last,Comp comp)
		:first_(std::move(first)),last_(std::move(last)),comp_(std::move(comp)){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::lexicographical_compare(r.cbegin(),r.cend(),std::move(first_),std::move(last_),std::move(comp_));
	}
private:
	Iterator first_,last_;
	Comp comp_;
};

template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr lexicographical_compare_range<std::decay_t<Range>> lexicographical_compare(Range&& r)
{
	return lexicographical_compare_range<std::decay_t<Range>>(std::forward<Range>(r));
}
template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr lexicographical_compare_iterator<std::decay_t<Iterator>> lexicographical_compare(Iterator&& first,Iterator&& last)
{
	return lexicographical_compare_iterator<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}
template<class Range,class Compare,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr lexicographical_compare_range_comp<std::decay_t<Range>,std::decay_t<Compare>> lexicographical_compare(Range&& r,Compare&& comp)
{
	return lexicographical_compare_range_comp<std::decay_t<Range>,std::decay_t<Compare>>(std::forward<Range>(r),std::forward<Compare>(comp));
}
template<class Iterator,class Compare,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr lexicographical_compare_iterator_comp<std::decay_t<Iterator>,std::decay_t<Compare>> lexicographical_compare(Iterator&& first,Iterator&& last,Compare&& comp)
{
	return lexicographical_compare_iterator_comp<
		std::decay_t<Iterator>,
		std::decay_t<Compare>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Compare>(comp));
}
	
} // inline namespace v1
} // namespace detail

using detail::lexicographical_compare;

} // namespace adaptors
} // namesapce srook

#endif
