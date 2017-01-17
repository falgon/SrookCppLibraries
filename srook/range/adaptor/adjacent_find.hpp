#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_ADJACENT_FIND_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_ADJACENT_FIND_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/adjacent_find.hpp>)
#define POSSIBLE_TO_BOOST_ADJACENT_FIND
#include<boost/range/algorithm/adjacent_find.hpp>
#elif
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
template<class Predicate>
struct adjacent_find_t_predicate{
	explicit constexpr adjacent_find_t_predicate(const Predicate& pred):pred_(pred){}
	explicit constexpr adjacent_find_t_predicate(Predicate&& pred):pred_(std::move(pred)){}
	template<class Range>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
		return boost::range::adjacent_find(std::forward<Range>(r),std::move(pred_));
#elif
		return std::adjacent_find(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr adjacent_find_t_predicate<std::decay_t<Predicate>> adjacent_find(Predicate&& pred_)
{
	return adjacent_find_t_predicate<std::decay_t<Predicate>>(std::forward<Predicate>(pred_));
}

struct adjacent_find_t{
	template<class Range>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
		return boost::range::adjacent_find(std::forward<Range>(r));
#elif
		return std::adjacent_find(r.cbegin(),r.cend());
#endif
	}
};
constexpr adjacent_find_t adjacent_find()
{
	return adjacent_find_t();
}

} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_ADJACENT_FIND
#undef POSSIBLE_TO_BOOST_ADJACENT_FIND
#endif
#endif
