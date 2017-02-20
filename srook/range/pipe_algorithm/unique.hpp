#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UNIQUE_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UNIQUE_HPP
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct unique_t{
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator
	operator()(Range&& r)
	{
		return std::unique(r.begin(),r.end());
	}
};

template<class BinaryPredicate>
struct unique_pred_t{
	template<REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>>)>
	explicit constexpr unique_pred_t(BinaryPredicate pred):pred_(std::move(pred)){}
	
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	typename std::remove_reference_t<std::remove_cv_t<Range>>::iterator
	operator()(Range&& r)
	{
		return std::unique(r.begin(),r.end(),std::move(pred_));
	}
private:
	BinaryPredicate pred_;
};

constexpr unique_t unique(){return unique_t();}

template<class BinaryPredicate,REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>>)>
constexpr unique_pred_t<std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>>
unique(BinaryPredicate&& pred)
{
	return unique_pred_t<
		std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>
	>(std::forward<BinaryPredicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::unique;

} // namespace pipealgo
} // namespace srook

#endif
