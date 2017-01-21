#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_EQUAL
#define INCLUDED_SROOK_RANGE_ADAPTOR_EQUAL
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<type_traits>
#if __has_include(<boost/range/algorithm/equal.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL
#include<boost/range/algorithm/equal.hpp>
#else
#include<algorithm>
#endif

#if __has_include(<optional>)
#define POSSIBLE_TO_INCLUDE_STD_OPTIONAL
#include<optional>
#elif __has_include(<boost/optional.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#include<boost/optional.hpp>
#else
#include<srook/optinal.hpp>
#endif

#define EQUAL_REQUIRE(...) std::enable_if_t<__VA_ARGS__,std::nullptr_t> =nullptr

namespace srook{
namespace adaptors{
inline namespace v1{

template<class Range>
struct equal_range_t{
	explicit constexpr equal_range_t(const Range& r):r_(r){}
	template<class R>
	bool operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL
		return boost::range::equal(std::forward<R>(r),r_);
#else
		return std::equal(r.cbegin(),r.cend(),r_.cbegin(),r_.cend());
#endif
	}
private:
	const Range& r_;
};

template<class Iterator>
struct equal_iterator_t{
	explicit constexpr equal_iterator_t(
			Iterator first,
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
			std::optional<Iterator> 
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL)
			boost::optional<Iterator>
#else
			srook::optional<Iterator>
#endif
			last
		)
		:first_(std::move(first)),
		last_(last?std::move(last.value()):last){}

	template<class Range>
	bool operator()(Range&& r)
	{
		if(last_)
			return std::equal(r.cbegin(),r.cend(),std::move(first_),std::move(last_.value()));
		else
			return std::equal(r.cbegin(),r.cend(),std::move(first_));
	}
private:
	Iterator first_;
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
	std::optional<Iterator>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL)
	boost::optional<Iterator>
#else
	srook::optional<Iterator>
#endif
	last_;
};

template<class Range,class Predicate>
struct equal_range_predicate_t{
	explicit constexpr equal_range_predicate_t(const Range& r,Predicate pred):r_(r),pred_(std::move(pred)){}
	
	template<class R>
	bool operator()(R&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL
		return boost::range::equal(std::forward<R>(r),r_,std::move(pred_));
#else
		return std::equal(r.cbegin(),r.cend(),r_.cbegin(),r_.cend(),std::move(pred_));
#endif
	}
private:
	const Range& r_;
	Predicate pred_;
};

template<class Iterator,class Predicate>
struct equal_iterator_predicate_t{
	explicit constexpr equal_iterator_predicate_t(Iterator first,Iterator last,Predicate pred)
		:first_(std::move(first)),last_(std::move(last)),pred_(std::move(pred)){}

	template<class Range>
	bool operator()(Range&& r)
	{
		return std::equal(r.cbegin(),r.cend(),std::move(first_),std::move(last_),std::move(pred_));
	}
private:
	Iterator first_,last_;
	Predicate pred_;
};


namespace mpl{
template<class,class=std::void_t<>>
constexpr bool has_iterator_v=std::false_type::value;
template<class T>
constexpr bool has_iterator_v<T,std::void_t<typename T::iterator>> =std::true_type::value;
}

template<class R,EQUAL_REQUIRE(mpl::has_iterator_v<std::decay_t<R>>)>
constexpr equal_range_t<std::decay_t<R>> equal(R&& range)
{
	return equal_range_t<std::decay_t<R>>(std::forward<R>(range));
}

template<class Iterator,EQUAL_REQUIRE(!mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr equal_iterator_t<std::decay_t<Iterator>> equal(
		Iterator&& first,
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
		std::optional<std::decay_t<Iterator>> last=std::nullopt
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL)
		boost::optional<std::decay_t<Iterator>> last=boost::none
#else
		srook::optional<std::decay_t<Iterator>> last=srook::nullopt
#endif
		)
{
	return equal_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::move(last));
}

template<class Range,class Predicate,EQUAL_REQUIRE(mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr equal_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>> equal(Range&& r,Predicate&& pred)
{
	return equal_range_predicate_t<std::decay_t<Range>,std::decay_t<Predicate>>(std::forward<Range>(r),std::forward<Predicate>(pred));
}

template<class Iterator,class Predicate>
constexpr equal_iterator_predicate_t<std::decay_t<Iterator>,std::decay_t<Predicate>> equal(Iterator&& first,Iterator&& last,Predicate&& pred)
{
	return equal_iterator_predicate_t<
				std::decay_t<Iterator>,
				std::decay_t<Predicate>
			>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_EQUAL
#endif
#ifdef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
#undef POSSIBLE_TO_INCLUDE_STD_OPTIONAL
#endif
#ifdef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#undef POSSIBLE_TO_INCLUDE_BOOST_OPTIONAL
#endif

#endif
