#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_IS_PARTITIONED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_IS_PARTITIONED_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/is_partitioned.hpp>)
#include<boost/range/algorithm/is_partitioned.hpp>
#define POSSIBLE_TO_BOOST_RANGE_PARTITIONED
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct is_partitioned_t{
	explicit constexpr is_partitioned_t(Predicate pred):pred_(std::move(pred)){}
	template<class Range>
	bool operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_BOOST_RANGE_PARTITIONED
		boost::range::is_partitioned(std::forward<Range>(r),std::move(pred_));
#else
		std::is_partitioned(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr is_partitioned_t<std::decay_t<Predicate>> is_partitioned(Predicate&& pred)
{
	return is_partitioned_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::is_partitioned;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_BOOST_RANGE_PARTITIONED
#undef POSSIBLE_TO_BOOST_RANGE_PARTITIONED
#endif
#endif
