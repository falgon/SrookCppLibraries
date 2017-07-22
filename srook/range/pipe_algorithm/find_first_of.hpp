// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ADAPTOR_FIND_FIRST_OF_HPP
#define INCLUDED_SROOK_ADAPTOR_FIND_FIRST_OF_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<type_traits>
#if __has_include(<boost/range/algorithm/find_first_of.hpp>)
#define POSSIBLE_TO_INCLUDE_RANGE_FIND_FIRST_OF
#include<boost/range/algorithm/find_first_of.hpp>
#else
#include<algorithm>
#endif
#if __has_include(<optional>)
#define POSSIBLE_TO_INCLUDE_STD_OPTIONAL
#include<optional>
#elif __has_include(<boost/optional.hpp>)
#define POSSIBLE_TOINCLUDE_BOOST_OPTIONAL
#include<boost/optional.hpp>
#else
#include<srook/optional.hpp>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Range>
struct find_first_of_range_t{
	template<REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	explicit constexpr find_first_of_range_t(const Range& r):r_(r){}
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<R>::const_iterator operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_RANGE_FIND_FIRST_OF
		return boost::range::find_first_of(std::forward<R>(r),r_);
#else
		return std::find_first_of(r.cbegin(),r.cend(),r_.cbegin(),r_.cend());
#endif
	}
private:
	const Range& r_;
};

template<>
struct find_first_of_range_t<std::string>{
	explicit find_first_of_range_t(
			const std::string& str,
			std::string::size_type pos=0
	)
		:data_(str),pos_(std::move(pos)){}

	explicit find_first_of_range_t(
			const std::string::value_type* str,
			std::string::size_type pos,
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
			std::optional<std::string::size_type>
#elif defined(POSSIBLE_TOINCLUDE_BOOST_OPTIONAL)
			boost::optional<std::string::size_type>
#else
			srook::optional<std::string::size_type>
#endif
			n)
		:data_(str),pos_(std::move(pos)),n_(n?std::move(n.value()):n){}

	std::string::size_type operator()(const std::string& str)
	{
		if(n_)
			return data_.find_first_of(str.c_str(),pos_,n_.value());
		else
			return data_.find_first_of(str,pos_);
	}
private:
	const std::string data_;
	std::string::size_type pos_;
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
	std::optional<std::string::size_type> n_=std::nullopt;
#elif defined(POSSIBLE_TOINCLUDE_BOOST_OPTIONAL)
	boost::optional<std::string::size_type> n_=boost::none;
#else
	srook::optional<std::string::size_type> n_=srook::nullopt;
#endif
};

template<class Iterator>
struct find_first_of_iterator_t{
	template<REQUIRES(!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>)>
	explicit constexpr find_first_of_iterator_t(const Iterator& first,const Iterator& last)
		:first_(first),last_(last){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return std::find_first_of(r.cbegin(),r.cend(),first_,last_);
	}
private:
	const Iterator& first_;
	const Iterator& last_;
};
template<class Range,class Predicate>
struct find_first_of_range_predicate_t{
	template<REQUIRES( (has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<Predicate> )>
	explicit constexpr find_first_of_range_predicate_t(const Range& r,const Predicate& pred)
		:r_(r),pred_(pred){}
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	typename std::decay_t<R>::const_iterator operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_RANGE_FIND_FIRST_OF
		return boost::range::find_first_of(std::forward<R>(r),r_,pred_);
#else
		return std::find_first_of(r.cbegin(),r.cend(),r_.cbegin(),r_.cend(),pred_);
#endif
	}
private:
	const Range& r_;
	const Predicate& pred_;
};

template<class Iterator,class Predicate>
struct find_first_of_iterator_predicate_t{
	
	template<REQUIRES( (!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>) && is_callable_v<Predicate> )>
	explicit constexpr find_first_of_iterator_predicate_t(const Iterator& first,const Iterator& last,const Predicate& pred)
		:first_(first),last_(last),pred_(pred){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return std::find_first_of(r.cbegin(),r.cend(),first_,last_,pred_);
	}
private:
	const Iterator& first_;
	const Iterator& last_;
	const Predicate& pred_;
};



template<class Range>
constexpr find_first_of_range_t<std::decay_t<Range>>
find_first_of(Range&& r)
{
	return find_first_of_range_t<std::decay_t<Range>>(std::forward<Range>(r));
}
template<class Iterator,REQUIRES(!::srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr find_first_of_iterator_t<std::decay_t<Iterator>>
find_first_of(Iterator&& first,Iterator&& last)
{
	return find_first_of_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}
template<class Range,class Predicate,REQUIRES(::srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr find_first_of_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>>
find_first_of(Range&& r,Predicate&& pred)
{
	return find_first_of_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>>(std::forward<Range>(r),std::forward<Predicate>(pred));
}
template<class Iterator,class Predicate>
constexpr find_first_of_iterator_predicate_t<std::decay_t<Iterator>,std::decay_t<Predicate>>
find_first_of(Iterator&& first,Iterator&& last,Predicate&& pred)
{
	return find_first_of_iterator_predicate_t<
				std::decay_t<Iterator>,
				std::decay_t<Predicate>
			>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Predicate>(pred));
}

find_first_of_range_t<std::string>
find_first_of(const std::string& str,std::string::size_type pos=0)
{
	return find_first_of_range_t<std::string>(str,pos);
}
find_first_of_range_t<std::string>
find_first_of(
		const std::string::value_type* s,
		std::string::size_type pos,
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
		std::optional<std::string::size_type> n=std::nullopt
#elif defined(POSSIBLE_TOINCLUDE_BOOST_OPTIONAL)
		boost::optional<std::string::size_type> n=boost::none
#else
		srook::optional<std::string::size_type> n=srook::nullopt
#endif
)
{
	return find_first_of_range_t<std::string>(s,std::move(pos),n);
}

} // inline namespace v1
} // namespace detail

using detail::find_first_of;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_RANGE_FIND_FIRST_OF
#undef POSSIBLE_TO_INCLUDE_RANGE_FIND_FIRST_OF
#endif
#undef FIND_FIRST_OF_REQUIRES
#endif
