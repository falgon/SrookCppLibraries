#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_COPIED_IF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_COPIED_IF_HPP
#include<srook/iterator/remove_copied_if_range_iterator.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator,class T>
struct remove_copied_if_range_t{
	template<REQUIRES(!has_iterator_v<Iterator>)>
	explicit constexpr remove_copied_if_range_t(Iterator first,Iterator last,const T& t)
		:first_(std::move(first)),last_(std::move(last)),value(t){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	operator Range()
	{
		return Range(make_remove_copied_if_range_iterator(first_,last_,value),make_remove_copied_if_range_iterator(last_,last_,value));
	}
private:
	Iterator first_,last_;
	const T& value;
};

template<class Iterator,class T>
constexpr remove_copied_if_range_t<std::decay_t<Iterator>,std::decay_t<T>>
make_remove_copied_if_range_t(Iterator&& first,Iterator&& last,T&& t)
{
	return remove_copied_if_range_t<std::decay_t<Iterator>,std::decay_t<T>>(std::forward<Iterator>(first),std::forward<Iterator>(last),std::forward<T>(t));
}

template<class Predicate>
struct remove_copied_if_t{
	template<REQUIRES(is_callable_v<Predicate>)>
	explicit constexpr remove_copied_if_t(const Predicate& t):pred_(t){}
	
	template<
		class Range,
		REQUIRES(std::is_const<std::remove_reference_t<Range>>::value)
	>
	constexpr remove_copied_if_range_t<
		typename std::remove_cv_t<std::decay_t<Range>>::const_iterator,
		std::remove_cv_t<std::decay_t<Predicate>>
	>
	operator()(Range&& r)
	{
		return remove_copied_if_range_t<
			typename std::remove_cv_t<std::decay_t<Range>>::const_iterator,
			std::remove_cv_t<std::decay_t<Predicate>>
		>(std::begin(r),std::end(r),std::move(pred_));
	}
	
	template<
		class Range,
		REQUIRES(!std::is_const<std::remove_reference_t<Range>>::value)
	>
	constexpr remove_copied_if_range_t<
		typename std::remove_cv_t<std::remove_reference_t<Range>>::iterator,
		std::remove_cv_t<std::remove_reference_t<Predicate>>
	>
	operator()(Range&& r)
	{
		return remove_copied_if_range_t<
			typename std::remove_cv_t<std::remove_reference_t<Range>>::iterator,
			std::remove_cv_t<std::remove_reference_t<Predicate>>
		>(std::begin(r),std::end(r),std::move(pred_));
	}

private:
	Predicate pred_;
};

template<class T>
constexpr remove_copied_if_t<std::decay_t<T>> remove_copied_if(T&& value)
{
	return remove_copied_if_t<std::decay_t<T>>(std::forward<T>(value));
}

} // inline namespace v1
} // namesapce detail

using detail::remove_copied_if;

} // namesapce adaptors
} // namespace srook
#endif
