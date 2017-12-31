// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_IS_PERMUTATION_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_IS_PERMUTATION_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Range>
struct is_permutation_range_t{
	template<REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	explicit constexpr is_permutation_range_t(const Range& r):r_(r){}
	

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)const
	{
		return std::is_permutation(r.cbegin(),r.cend(),r_.cbegin());
	}
private:
	const Range& r_;
};

template<class Iterator>
struct is_permutation_iterator_t{
	template<REQUIRES(!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>)>
	explicit constexpr is_permutation_iterator_t(Iterator iter):iter_(std::move(iter)){}
	
	template<class R,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::is_permutation(r.cbegin(),r.cend(),std::move(iter_));
	}
private:
	Iterator iter_;
};

template<class Iterator>
struct is_permutation_double_iterator_t{
	template<REQUIRES(!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>)>
	explicit constexpr is_permutation_double_iterator_t(Iterator first,Iterator last):first_(std::move(first)),last_(std::move(last)){}

	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::is_permutation(r.cbegin(),r.cend(),std::move(first_),std::move(last_));
	}
private:
	Iterator first_,last_;
};

template<class Range,class BinaryPredicate>
struct is_permutation_range_binarypredicate{
	template<REQUIRES( (has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<BinaryPredicate> )>
	explicit constexpr is_permutation_range_binarypredicate(const Range& r,const BinaryPredicate& pred):r_(r),pred_(pred){}
	
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)const
	{
		return std::is_permutation(r.cbegin(),r.cend(),r_.cbegin(),pred_);
	}
private:
	const Range& r_;
	const BinaryPredicate& pred_;
};

template<class Iterator,class BinaryPredicate>
struct is_permutation_iterator_binarypredicate{
	template<REQUIRES( (!has_iterator_v<Iterator> || is_range_iterator_v<Iterator>) && is_callable_v<BinaryPredicate> )>
	explicit constexpr is_permutation_iterator_binarypredicate(Iterator iter,const BinaryPredicate& pred)
		:iter_(std::move(iter)),pred_(pred){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::is_permutation(r.cbegin(),r.cend(),std::move(iter_),pred_);
	}
private:
	Iterator iter_;
	const BinaryPredicate& pred_;
};

template<class Iterator,class BinaryPredicate>
struct is_permutation_double_iterator_binarypredicate{
	template<REQUIRES( (!has_iterator_v<std::decay_t<Iterator>> || is_range_iterator_v<std::decay_t<Iterator>>) && is_callable_v<BinaryPredicate> )>
	explicit constexpr is_permutation_double_iterator_binarypredicate(Iterator first,Iterator last,const BinaryPredicate& pred)
		:first_(std::move(first)),last_(std::move(last)),pred_(pred){}
	
	template<class R,REQUIRES(has_iterator_v<std::decay_t<R>> || is_range_iterator_v<std::decay_t<R>>)>
	bool operator()(R&& r)
	{
		return std::is_permutation(r.cbegin(),r.cend(),std::move(first_),std::move(last_),pred_);
	}
private:
	Iterator first_,last_;
	const BinaryPredicate& pred_;
};

template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr is_permutation_range_t<std::decay_t<Range>> is_permutation(Range&& r)
{
	return is_permutation_range_t<std::decay_t<Range>>(std::forward<Range>(r));
}

template<class Iterator,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr is_permutation_iterator_t<std::decay_t<Iterator>> is_permutation(Iterator&& iter)
{
	return is_permutation_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<class Iterator>
constexpr is_permutation_double_iterator_t<std::decay_t<Iterator>> is_permutation(Iterator&& first,Iterator&& last)
{
	return is_permutation_double_iterator_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}

template<class Range,class BinaryPredicate,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
constexpr is_permutation_range_binarypredicate<std::decay_t<Range>,std::decay_t<BinaryPredicate>> is_permutation(Range&& r,BinaryPredicate&& pred)
{
	return is_permutation_range_binarypredicate<std::decay_t<Range>,std::decay_t<BinaryPredicate>>(std::forward<Range>(r),std::forward<BinaryPredicate>(pred));
}

template<class Iterator,class BinaryPredicate,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr is_permutation_iterator_binarypredicate<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>> is_permutation(Iterator&& iter,BinaryPredicate&& pred)
{
	return is_permutation_iterator_binarypredicate<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>>(std::forward<Iterator>(iter),std::forward<BinaryPredicate>(pred));
}

template<class Iterator,class BinaryPredicate,REQUIRES(!srook::mpl::has_iterator_v<std::decay_t<Iterator>>)>
constexpr is_permutation_double_iterator_binarypredicate<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>>
is_permutation(Iterator&& first,Iterator&& last,BinaryPredicate&& pred)
{
	return is_permutation_double_iterator_binarypredicate<std::decay_t<Iterator>,std::decay_t<BinaryPredicate>>(
				std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<BinaryPredicate>(pred)
			);
}

} // inilne namespace v1
} // namespace detail

using detail::is_permutation;

} // namespace pipealgo
} // namespace srook


#endif
