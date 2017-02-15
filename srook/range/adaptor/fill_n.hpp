#ifndef INCLUDED_SROOK_ADAPTOR_FILL_N_HPP
#define INCLUDED_SROOK_ADAPTOR_FILL_N_HPP
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

template<class T>
struct fill_n_t{
	explicit constexpr fill_n_t(const std::size_t& size,const T& t):size_(size),value_(t){}
	explicit constexpr fill_n_t(std::size_t&& size,const T& t):size_(std::move(size)),value_(t){}
	explicit constexpr fill_n_t(const std::size_t& size,T&& t):size_(size),value_(std::move(t)){}
	explicit constexpr fill_n_t(std::size_t&& size,T&& t):size_(std::move(size)),value_(std::move(t)){}

	template<class OutputIterator,REQUIRES(!has_iterator_v<std::decay_t<OutputIterator>>)>
	std::decay_t<OutputIterator> operator()(OutputIterator&& iter)
	{
		return std::fill_n(std::forward<OutputIterator>(iter),size_,value_);
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
} // namespace detail

using detail::fill_n;

} // namespace adaptors
} // namespace srook

#endif
