#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_FOR_EACH
#define INCLUDED_SROOK_RANGE_ADAPTOR_FOR_EACH
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/for_each.hpp>)
#include<boost/range/algorithm/for_each.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FOR_EACH
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Predicate>
struct for_each_t{
	explicit constexpr for_each_t(Predicate pred):pred_(std::move(pred)){}
	template<class Range>
	auto operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FOR_EACH
		return boost::range::for_each(std::forward<Range>(r),std::move(pred_));
#else
		return std::for_each(r.begin(),r.end(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};

template<class Predicate>
constexpr for_each_t<std::decay_t<Predicate>> for_each(Predicate&& pred)
{
	return for_each_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

}// inline namespace v1
}// namesapce detail

using detail::for_each;

}// namespace adaptors
}// namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FOR_EACH
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FOR_EACH
#endif
#endif
