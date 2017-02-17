#ifndef INCLUDED_SROOK_ADAPTOR_FIND_END_HPP
#define INCLUDED_SROOK_ADAPTOR_FIND_END_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>

#if __has_include(<boost/range/algorithm/find_end.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_END
#include<boost/range/algorithm/find_end.hpp>
#else
#include<algorithm>
#endif
namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Iterator>
struct find_end_iterator_t{
	explicit constexpr find_end_iterator_t(const Iterator& first,const Iterator& last)
		:first_(first),last_(last){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return std::find_end(r.cbegin(),r.cend(),first_,last_);
	}
private:
	const Iterator& first_;
	const Iterator& last_;
};

template<class Range>
struct find_end_range_t{
	explicit constexpr find_end_range_t(const Range& r):r_(r){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<R>::const_iterator operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_END
		return boost::range::find_end(std::forward<R>(r),r_);
#else
		return std::find_end(r.cbegin(),r.cend(),r_.cbegin(),r_.cend());
#endif
	}
private:
	const Range& r_;
};

template<class Iterator,class Predicate>
struct find_end_iterator_predicate_t{
	template<REQUIRES( (!has_iterator_v<std::decay_t<Iterator>> || is_range_iterator_v<std::decay_t<Iterator>>) && is_callable_v<std::decay_t<Predicate>> )>
	explicit constexpr find_end_iterator_predicate_t(const Iterator& first,const Iterator& last,const Predicate& pred)
		:first_(first),last_(last),pred_(pred){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return std::find_end(r.cbegin(),r.cend(),first_,last_,pred_);
	}
private:
	const Iterator& first_;
	const Iterator& last_;
	const Predicate& pred_;
};

template<class Range,class Predicate>
struct find_end_range_predicate_t{
	template<REQUIRES( (has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<std::decay_t<Predicate>> )>
	explicit constexpr find_end_range_predicate_t(const Range& r,const Predicate& pred)
		:r_(r),pred_(pred){}
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<R>::const_iterator operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FIND_END
		return boost::range::find_end(std::forward<R>(r),r_,pred_);
#else
		return std::find_end(r.cbegin(),r.cend(),r_.cbegin(),r_.cend(),pred_);
#endif
	}
private:
	const Range& r_;
	const Predicate& pred_;
};

template<class Iterator>
constexpr find_end_iterator_t<std::decay_t<Iterator>> find_end(Iterator&& first,Iterator&& last)
{
	return find_end_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}
template<class Range>
constexpr find_end_range_t<std::decay_t<Range>> find_end(Range&& r)
{
	return find_end_range_t<std::decay_t<Range>>(std::forward<Range>(r));
}
template<class Iterator,class Predicate>
constexpr find_end_iterator_predicate_t<std::decay_t<Iterator>,std::decay_t<Predicate>> find_end(Iterator&& first,Iterator&& last,Predicate&& pred)
{
	return find_end_iterator_predicate_t<
				std::decay_t<Iterator>,
				std::decay_t<Predicate>
			>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Predicate>(pred));
}
template<class Range,class Predicate>
constexpr find_end_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>> find_end(Range&& r,Predicate&& pred)
{
	return find_end_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>>(std::forward<Range>(r),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::find_end;

} // namespace pipealgo
} // namespace srook
#endif
