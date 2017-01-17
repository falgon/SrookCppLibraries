#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/algorithm/cxx11/all_of.hpp>)
#define POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#include<boost/algorithm/cxx11/all_of.hpp>
#elif
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
inline namespace v1{
template<class Predicate>
struct all_of_t{
	explicit constexpr all_of_t(const Predicate& pred):pred_(pred){}
	explicit constexpr all_of_t(Predicate&& pred):pred_(std::move(pred)){}
	template<class Range>
	bool operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
		return boost::algorithm::all_of(std::forward<Range>(r),std::move(pred_));
#elif
		return std::all_of(r.cbegin(),r.cend(),std::move(pred_));
#endif
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
} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#undef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#endif
#endif
