#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MISMATCH_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MISMATCH_HPP
#if __has_include(<boost/range/algorithm/mismatch.hpp>)
#include<boost/range/algorithm/mismatch.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_MISMATCH
#endif
#include<srook/iterator/range_iterator.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/remove_all_reference.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/mpl/variadic_player.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{

inline namespace v1{

template<class Iterator>
struct mismatch_iterator_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr mismatch_iterator_t(Iterator iter):iter_(std::move(iter)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,Iterator> operator()(R&& r)
	{
		return std::mismatch(r.cbegin(),r.cend(),std::move(iter_));
	}
private:
	Iterator iter_;
};

template<class Iterator,class BinaryPredicate>
struct mismatch_iterator_binarypredicate{
	template<REQUIRES( (!srook::mpl::has_iterator_v<Iterator> || is_range_iterator_v<std::decay_t<Iterator>>) && srook::is_callable_v<BinaryPredicate> )>
	explicit constexpr mismatch_iterator_binarypredicate(Iterator iter,BinaryPredicate binary_pred)
		:iter_(std::move(iter)),pred_(std::move(binary_pred)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,Iterator> operator()(R&& r)
	{
		return std::mismatch(r.cbegin(),r.cend(),std::move(iter_),std::move(pred_));
	}
private:
	Iterator iter_;
	BinaryPredicate pred_;
};

template<class Iterator>
struct mismatch_iterators_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr mismatch_iterators_t(Iterator first,Iterator last):first_(std::move(first)),last_(std::move(last)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,Iterator> operator()(R&& r)
	{
		return std::mismatch(r.cbegin(),r.cend(),std::move(first_),std::move(last_));
	}
private:
	Iterator first_,last_;
};

template<class Range>
struct mismatch_ranges_t{
	template<REQUIRES(srook::mpl::has_iterator_v<Range> || is_range_iterator_v<std::decay_t<Range>>)>
	explicit constexpr mismatch_ranges_t(const Range& r):r_(r){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,typename Range::const_iterator> operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MISMATCH
		boost::range::mismatch(std::forward<R>(r),r_);
#else
		std::mismatch(r.cbegin(),r.cend(),r_.cbegin(),r_.cend());
#endif
	}
private:
	const Range& r_;
};

template<class Iterator,class BinaryPredicate>
struct mismatch_iterators_binarypredicate_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator> && srook::is_callable_v<BinaryPredicate>)>
	explicit constexpr mismatch_iterators_binarypredicate_t(Iterator first,Iterator last,BinaryPredicate binary_pred)
		:first_(std::move(first)),last_(std::move(last)),pred_(std::move(binary_pred)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,Iterator> operator()(R&& r)
	{
		return std::mismatch(r.cbegin(),r.cend(),std::move(first_),std::move(last_),std::move(pred_));
	}
private:
	Iterator first_,last_;
	BinaryPredicate pred_;
};

template<class Range,class BinaryPredicate>
struct mismatch_ranges_binarypredicate_t{
	template<REQUIRES( (srook::mpl::has_iterator_v<Range> || is_range_iterator_v<std::decay_t<Range>>) && srook::is_callable_v<BinaryPredicate>)>
	explicit constexpr mismatch_ranges_binarypredicate_t(const Range& r,BinaryPredicate binary_pred)
		:r_(r),pred_(std::move(binary_pred)){}

	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	std::pair<typename std::decay_t<R>::const_iterator,typename Range::const_iterator> operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MISMATCH
		boost::range::mismatch(std::forward<R>(r),r_,std::move(pred_));
#else
		std::mismatch(r.cbegin(),r.cend(),r_.cbegin(),r_.cend(),std::move(pred_));
#endif
	}
private:
	const Range& r_;
	BinaryPredicate pred_;
};

template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr mismatch_iterator_t<std::decay_t<Iterator>> mismatch(Iterator&& iter)
{
	return mismatch_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<
	class Iterator,
	class BinaryPredicate,
	REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>> && srook::is_callable_v<std::decay_t<BinaryPredicate>>)
>
constexpr mismatch_iterator_binarypredicate<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>> mismatch(Iterator&& iter,BinaryPredicate&& binary_pred)
{
	return mismatch_iterator_binarypredicate<
		std::decay_t<Iterator>,
		std::decay_t<BinaryPredicate>
	>(std::forward<Iterator>(iter),std::forward<BinaryPredicate>(binary_pred));
}

template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr mismatch_iterators_t<std::decay_t<Iterator>> mismatch(Iterator first,Iterator last)
{
	return mismatch_iterators_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}

template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr mismatch_ranges_t<std::decay_t<Range>> mismatch(Range&& r)
{
	return mismatch_ranges_t<std::decay_t<Range>>(std::forward<Range>(r));
}

template<
	class Iterator,
	class BinaryPredicate,
	REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>> && srook::is_callable_v<std::decay_t<BinaryPredicate>>)
>
constexpr mismatch_iterators_binarypredicate_t<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>> mismatch(Iterator&& first,Iterator&& last,BinaryPredicate&& binary_pred)
{
	return mismatch_iterators_binarypredicate_t<
			std::decay_t<Iterator>,
			std::decay_t<BinaryPredicate>
	>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<BinaryPredicate>(binary_pred));
}

template<
	class Range,
	class BinaryPredicate,
	REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> && srook::is_callable_v<std::decay_t<BinaryPredicate>>)
>
constexpr mismatch_ranges_binarypredicate_t<std::decay_t<Range>,std::decay_t<BinaryPredicate>> mismatch(Range&& r,BinaryPredicate&& binary_pred)
{
	return mismatch_ranges_binarypredicate_t<
			std::decay_t<Range>,
			std::decay_t<BinaryPredicate>
	>(std::forward<Range>(r),std::forward<BinaryPredicate>(binary_pred));
}

} // inlin namespace v1
} // namespace detail

using detail::mismatch;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MISMATCH
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MISMATCH
#endif

#endif
