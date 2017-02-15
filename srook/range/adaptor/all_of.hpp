#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{
template<class Predicate>
struct all_of_t{
	explicit constexpr all_of_t(const Predicate& pred):pred_(pred){}
	explicit constexpr all_of_t(Predicate&& pred):pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::all_of(r.cbegin(),r.cend(),std::move(pred_));
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr all_of_t<std::decay_t<Predicate>> all_of(Predicate&& pred)
{
	return all_of_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::all_of;

} // namespace adaptors
} // namespace srook
#endif
