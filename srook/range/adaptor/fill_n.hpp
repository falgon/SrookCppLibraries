#ifndef INCLUDED_SROOK_ADAPTOR_FILL_N_HPP
#define INCLUDED_SROOK_ADAPTOR_FILL_N_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/adaptor/fill_n.hpp>)
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL_N
#include<boost/range/adaptor/fill_n.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
inline namespace v1{

template<class T>
struct fill_n_t{
	explicit constexpr fill_n_t(const std::size_t& size,const T& t):size_(size),value_(t){}
	explicit constexpr fill_n_t(std::size_t&& size,const T& t):size_(std::move(size)),value_(t){}
	explicit constexpr fill_n_t(const std::size_t& size,T&& t):size_(size),value_(std::move(t)){}
	explicit constexpr fill_n_t(std::size_t&& size,T&& t):size_(std::move(size)),value_(std::move(t)){}

	template<class OutputIterator>
	std::decay_t<OutputIterator> operator()(OutputIterator&& iter)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL_N
		return boost::range::fill_n(std::forward<OutputIterator>(iter),size_,value_);
#else
		return std::fill_n(std::forward<OutputIterator>(iter),size_,value_);
#endif
	}
private:
	std::size_t size_;
	T value_;
};
template<class T>
constexpr fill_n_t<std::decay_t<T>> fill_n(std::size_t x,T&& value)
{
	return fill_n_t<std::decay_t<T>>(std::move(x),std::forward<T>(value));
}

} // inline namespace v1
} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL_N
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_FILL_N
#endif
#endif
